from collections.abc import Iterable
from os import PathLike
from pathlib import Path

HEADER_SUFFIXES = (".h", ".hpp", ".hxx")


def _raise_walk_error(error: OSError) -> None:
    raise error


def make_header(
    directory: str | PathLike[str],
    header_name: str,
    exclude: Iterable[str] = (),
) -> None:
    root = Path(directory).resolve()

    if header_name in {"", ".", ".."} or Path(header_name).name != header_name:
        raise ValueError("`header_name` must be a single file name")

    target = root / header_name
    excluded_names = set(exclude) | {header_name}
    include_paths: list[str] = []

    for dirpath, dirnames, filenames in root.walk(
        top_down=True,
        on_error=_raise_walk_error,
        follow_symlinks=False,
    ):
        dirnames[:] = [name for name in dirnames if name not in excluded_names]

        for filename in filenames:
            if filename in excluded_names or not filename.endswith(HEADER_SUFFIXES):
                continue

            path = dirpath / filename

            # `Path.walk` lists directory symlinks among filenames.
            if path.is_dir():
                continue

            include_paths.append(path.relative_to(root.parent).as_posix())

    include_paths.sort()

    content = (
        "\n".join(
            [
                "#pragma once",
                "",
                "// IWYU pragma: begin_exports",
                *(f'#include "{path}"' for path in include_paths),
                "// IWYU pragma: end_exports",
            ]
        )
        + "\n"
    )

    encoded_content = content.encode("utf-8")

    try:
        if target.read_bytes() == encoded_content:
            return
    except FileNotFoundError:
        pass

    target.write_bytes(encoded_content)


def main() -> None:
    project_root = Path(__file__).resolve().parents[2]
    include_root = project_root / "src"

    make_header(include_root / "F4SE", "F4SE.hpp", exclude={"Impl"})
    make_header(
        include_root / "RE",
        "RE.hpp",
        exclude={
            "CoreTypes.hpp",
            "IDs.hpp",
            "IDs_NiRTTI.hpp",
            "IDs_RTTI.hpp",
            "IDs_VTABLE.hpp",
            "NiRTTI.hpp",
            "Offsets.hpp",
            "RTTI.hpp",
        },
    )
    make_header(include_root / "Scaleform", "Scaleform.hpp")
    make_header(include_root / "msvc", "msvc.hpp")


if __name__ == "__main__":
    main()
