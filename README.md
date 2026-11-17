# CommonLibF4 AV

[![Standard](https://img.shields.io/static/v1?label=Standard&message=C%2B%2B%2023&color=blue&logo=c%2B%2B&&logoColor=white&style=flat)](https://en.cppreference.com/cpp/compiler_support#C++23_features)
[![Platform](https://img.shields.io/static/v1?label=Platform&message=Windows%20x64&color=dimgray&style=flat)](https://learn.microsoft.com/de-de/windows/apps/windows-sdk/downloads#windows-10)

## About

This is an All Versions (AV) fork of CommonLibF4 which makes it possible to support multiple game versions at the same time without having to ship separate builds.

It currently supports Old-Gen (OG; v1.10.163.0), Next-Gen (NG; v1.10.984.0) and Anniversary Edition (AE; v1.11.240.0+).

The project is based on [alandtse's](https://github.com/alandtse) [CommonLibF4 NG](https://github.com/alandtse/CommonLibF4), with many additions, improvements and fixes.

## Build Requirements

- [CMake](https://cmake.org)
- [vcpkg](https://github.com/microsoft/vcpkg)
- [MSVC](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2026) or
  [clang-cl](https://github.com/llvm/llvm-project) with [ninja](https://github.com/ninja-build/ninja)

## End-User Requirements

- For normal builds:
  - [F4SE](https://f4se.silverlock.org)
  - [Address Library for F4SE Plugins](https://nexusmods.com/fallout4/mods/47327)
- For VR-compatible builds:
  - [F4SEVR](https://f4se.silverlock.org)
  - [Address Library VR for F4SEVR Plugins](https://nexusmods.com/fallout4/mods/64879)

## Getting Started

To clone the project, execute:

```shell
git clone --recurse-submodules https://github.com/LucaDotGit/CommonLibF4
cd CommonLibF4
```

To build the project, execute:

```shell
cmake build
```

## Notes

- CommonLibF4 is intended to replace F4SE as a static dependency. However, the runtime component of F4SE is still required.
- For more information about VR development, see [alandtse's build](https://github.com/alandtse/CommonLibF4).

## License

[GPL-3.0-or-later](LICENSE.md) WITH [Modding Exception and Linking Exception (with Corresponding Source)](EXCEPTIONS.md).

Specifically, the **Modded Code** is Fallout 4 (and its variants) and **Modding Libraries** include [F4SE](https://f4se.silverlock.org) ([GitHub](https://github.com/ianpatt/f4se)).

It is recommended to read the [FSF FAQ](https://gnu.org/licenses/gpl-faq.en.html) for a full explanation on what this license requires.

The main requirement of this license is: if you link your mod against CommonLibF4, and you distribute the binaries for that mod,
you must also distribute the source code under the same license as CommonLibF4 along with the source code for any other libraries you link against,
with the exception of the Modded Code and Modding Libraries defined above.

Originally based on code under [MIT](./assets/licenses/MIT.md).

## Credits

- Thanks to [Ryan McKenzie](https://github.com/Ryan-rsm-McKenzie) for the [initial code](https://github.com/Ryan-rsm-McKenzie/CommonLibF4)
- Thanks to [alandtse](https://github.com/alandtse) for the [Next-Gen and VR ports](https://github.com/alandtse/CommonLibF4)
- Thanks to the maintainers of active forks:
  - [powerof3](https://github.com/powerof3/CommonLibF4)
  - [shad0wshayd3 and quidx](https://github.com/libxse/commonlibf4)
