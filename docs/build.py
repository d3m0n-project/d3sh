
#!/usr/bin/env python3

from io import TextIOWrapper
import os
import re
from typing import Any

SRC_DIR = "src"
DOCS_DIR = "docs"


def get_defines(content: str) -> dict[str, str]:
    content = re.sub(r"\\\r?\n", "", content)

    pattern = re.compile(r'^\s*#\s*define\s+([A-Za-z_]\w*)\s+(.+?)\s*$', re.MULTILINE)
    defines = {}
    for match in pattern.finditer(content):
        name = match.group(1)
        value = match.group(2).strip()
        defines[name] = value
    return defines



def resolve_define(name: str, defines: dict[str, str], default: Any = None, seen: set[str] | None = None) -> Any:
    if name not in defines:
        return default

    if seen is None:
        seen = set()

    if name in seen:
        return default

    seen.add(name)
    value = defines[name]
    tokens = re.findall(
        r'"(?:\\.|[^"\\])*"|[A-Za-z_]\w*',
        value
    )

    result = []
    for token in tokens:
        if token.startswith('"'):
            result.append(token[1:-1])
        elif token in defines:
            resolved = resolve_define(token, defines, default="", seen=seen.copy())
            if isinstance(resolved, str):
                result.append(resolved)
        else:
            result.append(token)

    if result:
        return ''.join(result)

    return value



def get_define(name: str, defines: dict[str, str], default: Any = None) -> Any:
    return resolve_define(name, defines, default)


def main(readme: TextIOWrapper[Any]) -> None:
    programs = {}

    for file in os.listdir(SRC_DIR):
        if not file.endswith('.c'):
            continue

        program_name = os.path.basename(file).lower().removesuffix('.c')
        with open(os.path.join(SRC_DIR, file), 'r', encoding='utf-8') as f:
            content = f.read()

        defines = get_defines(content)
        programs[program_name] = {
            "name": get_define("PROGRAM_NAME", defines, "unknown program"),
            "author": get_define("PROGRAM_AUTHOR", defines, "unknown author"),
            "description": get_define("PROGRAM_DESCRIPTION", defines),
            "usage": get_define("PROGRAM_USAGE", defines),
            "examples": get_define("PROGRAM_EXAMPLES", defines, []),
            "args": get_define("PROGRAM_ARGUMENTS", defines, [])
        }
        print(f"- [{program_name}](./{program_name}), {programs[program_name]['description']}", file=readme)

		# write utility file
        with open(os.path.join(DOCS_DIR, f"{program_name}.md")) as utility:
            print("# d3sh Shell Utilities\n", file=utility)
        

    print(programs['basename'])


if __name__ == "__main__":
    with open(os.path.join(DOCS_DIR, "README.md"), 'w') as readme:
        print("# d3sh Shell Utilities\n", file=readme)
        print("## Utilities", file=readme)
        main(readme)
