
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
    tokens = re.findall(r'"(?:\\.|[^"\\])*"|[A-Za-z_]\w*', value)

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


def main(readme) -> None:
    programs = {}

    for file in os.listdir(SRC_DIR):
        if not file.endswith('.c'):
            continue

        program_name = os.path.basename(file).lower().removesuffix('.c')
        with open(os.path.join(SRC_DIR, file), 'r', encoding='utf-8') as f:
            content = f.read()
            #content = content.replace('\\n', '\n').replace('\\t', '\t')

        defines = get_defines(content)
        programs[program_name] = {
            "name": get_define("PROGRAM_NAME", defines, "unknown program"),
            "author": get_define("PROGRAM_AUTHOR", defines, "unknown author"),
            "description": get_define("PROGRAM_DESCRIPTION", defines),
            "usage": get_define("PROGRAM_USAGE", defines),
            "examples": get_define("PROGRAM_EXAMPLES", defines, "").split('\n'),
            "args": get_define("PROGRAM_ARGUMENTS", defines, "").split('\n')
        }
        print(f"- [{program_name}](./{program_name}.md) {programs[program_name]['description'] or ''}", file=readme)

		# write utility file
        with open(os.path.join(DOCS_DIR, f"{program_name}.md"), 'w') as utility:
            print(f"# {program_name.title()}\n", file=utility)

            infos = programs[program_name]
            print(f"Usage: {infos['usage']}", file=utility) if infos['usage'] else ...
            print(infos['description'], file=utility, end='\n\n') if infos['description'] else ...

            print(f"Mandatory arguments to long options are mandatory for short options too.", file=utility)  if len(infos['args']) > 0 else ...
            for arg in infos['args']:
                print(f"  {arg}", file=utility)

            print("\nExamples:", file=utility)
            for example in infos['examples']:
                print(f"  {example}", file=utility)

            print("\nd3sh Shell Utils: <https://github.com/d3m0n-project/d3sh>", file=utility, end='')        

    print(programs['basename'])


if __name__ == "__main__":
    with open(os.path.join(DOCS_DIR, "README.md"), 'w') as readme:
        print("# d3sh Shell Utilities\n", file=readme)
        print("## Utilities", file=readme)
        main(readme)
