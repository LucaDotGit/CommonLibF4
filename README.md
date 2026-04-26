# `CommonLibF4 AV`
[![Standard](https://img.shields.io/static/v1?label=Standard&message=C%2B%2B%2023&color=blue&logo=c%2B%2B&&logoColor=white&style=flat)](https://en.cppreference.com/w/cpp/compiler_support)
[![Platform](https://img.shields.io/static/v1?label=Platform&message=Windows%20x64&color=dimgray&style=flat)](#)

## About

This is an All Versions (AV) fork of CommonLibF4 which makes it possible to support multiple game versions at the same time without having to ship separate builds.
It currently supports Old-Gen (OG; v1.10.163.0), Next-Gen (NG; v1.10.984.0) and Anniversary Edition (AE; v1.11.191.0+).

The project is based on [alandtse's](https://github.com/alandtse) [CommonLibF4 NG](https://github.com/alandtse/CommonLibF4), with many additions, improvements and fixes.

## General Requirements

### Build Dependencies

- A C++ 23 compiler:
  - [MSVC 2026](https://learn.microsoft.com/en-us/visualstudio/releases/2026/release-history#release-dates-and-build-numbers)
  - [clang-cl](https://github.com/llvm/llvm-project) with [ninja](https://github.com/ninja-build/ninja)
- [fmt](https://github.com/fmtlib/fmt)
- [spdlog](https://github.com/gabime/spdlog)

### Development

- [CMake v4.3.0+](https://cmake.org)
- [vcpkg](https://github.com/microsoft/vcpkg)
  - Create an environmental variable called `VCPKG_ROOT` where the value is the path to your vcpkg installation.

## F4SE Requirements

### End User Dependencies

- [F4SE/VR](https://f4se.silverlock.org)
- [Address Library for F4SE Plugins](https://www.nexusmods.com/fallout4/mods/47327)
- [VR Address Library for F4SEVR Plugins](https://www.nexusmods.com/fallout4/mods/64879)

### Development

- [Address Library for F4SE Plugins](https://www.nexusmods.com/fallout4/mods/47327)
- [VR Address Library for F4SEVR Plugins](https://www.nexusmods.com/fallout4/mods/64879)

## Getting Started

To clone the project, run the following command:

```Batch
git clone --recurse-submodules https://github.com/LucaDotGit/CommonLibF4
cd CommonLibF4
```

### Build

To build the project, run the following command:

```Batch
cmake build
```

## Notes

- CommonLibF4 is intended to replace F4SE as a static dependency. However, the runtime component of F4SE is still required.
- For more information about VR development, see [alandtse's build](https://github.com/alandtse/CommonLibF4)

## Credits

- Thanks to [Ryan McKenzie](https://github.com/Ryan-rsm-McKenzie) for the [initial code](https://github.com/Ryan-rsm-McKenzie/CommonLibF4)
- Thanks to [alandtse](https://github.com/alandtse) for the [Next-Gen and VR ports](https://github.com/alandtse/CommonLibF4)
- Thanks to maintainers of active forks:
  - [powerof3](https://github.com/powerof3/CommonLibF4)
  - [shad0wshayd3 and quidx](https://github.com/libxse/commonlibf4)
