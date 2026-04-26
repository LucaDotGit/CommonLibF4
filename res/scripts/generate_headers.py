import os
import pathlib


def make_header(a_directory: str, a_fileName: str, a_exclude: set[str] = set()):
    HEADER_EXTENSIONS = (".h", ".hpp", ".hxx")

    a_exclude.add(a_fileName)

    with open(file=a_directory + "/" + a_fileName, mode="w", encoding="utf-8", newline="\n") as out:
        out.write("#pragma once\n")
        out.write("\n")

        out.write("// IWYU pragma: begin_exports\n")

        temp: list[str] = []
        for dirpath, dirnames, fileNames in os.walk(a_directory):
            rem: list[str] = []
            for dirname in dirnames:
                if dirname in a_exclude:
                    rem.append(dirname)
            for toDo in rem:
                dirnames.remove(toDo)

            for fileName in fileNames:
                if fileName not in a_exclude and fileName.endswith(HEADER_EXTENSIONS):
                    path = os.path.join(dirpath, fileName)
                    temp.append(os.path.normpath(path))

        files: list[str] = []
        for file in temp:
            files.append(file.replace("\\", "/"))

        files.sort()
        for file in files:
            out.write("#include \"")
            out.write(file)
            out.write("\"\n")

        out.write("// IWYU pragma: end_exports\n")


def main():
    root = pathlib.Path(os.path.dirname(
        os.path.realpath(__file__))).parent.parent
    os.chdir(os.path.join(root, "include"))

    # make_header("F4SE", "F4SE.hpp")
    make_header("RE", "Game.hpp", a_exclude={
                "CoreTypes.hpp",
                "IDs.hpp",
                "IDs_NiRTTI.hpp",
                "IDs_RTTI.hpp",
                "IDs_VTABLE.hpp",
                "NiRTTI.hpp",
                "Offsets.hpp",
                "RTTI.hpp"})
    make_header("msvc", "msvc.hpp")
    make_header("Scaleform", "Scaleform.hpp")


if __name__ == "__main__":
    main()
