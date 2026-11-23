#!/usr/bin/env python3
"""Generate utility manuals from PROGRAM_* documentation macros in src/*.c."""

import ast
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SRC_DIR = ROOT / "src"
DOCS_DIR = Path(__file__).resolve().parent


def get_defines(content: str) -> dict[str, str]:
    """Collect object-like defines, including backslash-continued values."""
    content = re.sub(r"\\\r?\n[\t ]*", "", content)
    pattern = re.compile(r"^\s*#\s*define\s+([A-Za-z_]\w*)\s+(.+?)\s*$", re.MULTILINE)
    return {match.group(1): match.group(2).strip() for match in pattern.finditer(content)}


def get_define(name: str, defines: dict[str, str], default: str = "") -> str:
    """Decode adjacent C string literals in a documentation macro."""
    value = defines.get(name)
    if value is None:
        return default
    literals = re.findall(r'"(?:\\.|[^"\\])*"', value)
    if not literals:
        return value.strip()
    return "".join(ast.literal_eval(literal) for literal in literals)


def read_program(source: Path) -> dict[str, object]:
    defines = get_defines(source.read_text(encoding="utf-8"))
    required = ("PROGRAM_DESCRIPTION", "PROGRAM_USAGE", "PROGRAM_ARGUMENTS", "PROGRAM_EXAMPLES")
    missing = [macro for macro in required if macro not in defines]
    if missing:
        raise ValueError(f"{source.relative_to(ROOT)} is missing documentation macros: {', '.join(missing)}")

    name = get_define("PROGRAM_NAME", defines, source.stem)
    return {
        "name": name,
        "author": get_define("PROGRAM_AUTHOR", defines, "Unknown"),
        "description": get_define("PROGRAM_DESCRIPTION", defines),
        "usage": get_define("PROGRAM_USAGE", defines),
        "arguments": [line for line in get_define("PROGRAM_ARGUMENTS", defines).splitlines() if line.strip()],
        "examples": [line for line in get_define("PROGRAM_EXAMPLES", defines).splitlines() if line.strip()],
    }


def write_program_page(slug: str, info: dict[str, object]) -> None:
    lines = [
        f"# {info['name']}", "", str(info["description"]), "", "## Usage", "",
        "```sh", str(info["usage"]), "```", "", "## Arguments", "",
    ]
    arguments = info["arguments"]
    if arguments:
        lines.extend(f"- {argument}" for argument in arguments)
    else:
        lines.append("This command takes no operands.")
    lines.extend(["", "## Examples", ""])
    for example in info["examples"]:
        lines.extend(["```sh", str(example), "```", ""])
    lines.extend([
        "## Details", "",
        "All utilities also accept `-v` or `--version` as the first argument to print the utility version and build date.",
        "", f"Author: {info['author']}.", "", "[Back to the utility index](README.md).", "",
    ])
    (DOCS_DIR / f"{slug}.md").write_text("\n".join(lines), encoding="utf-8")


def main() -> None:
    sources = sorted(SRC_DIR.glob("*.c"), key=lambda path: path.stem.lower())
    if not sources:
        raise SystemExit(f"No C programs found in {SRC_DIR}")
    programs = [(source.stem.lower(), read_program(source)) for source in sources]

    index = ["# d3sh Shell Utilities", "", "Utilities provided by this build:", ""]
    index.extend(f"- [{info['name']}](./{slug}.md) - {info['description']}" for slug, info in programs)
    index.append("")
    (DOCS_DIR / "README.md").write_text("\n".join(index), encoding="utf-8")
    for slug, info in programs:
        write_program_page(slug, info)


if __name__ == "__main__":
    main()
