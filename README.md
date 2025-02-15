# `CommonLibF4 NG`
[![C++23](https://img.shields.io/static/v1?label=Standard&message=C%2B%2B23&color=blue&logo=c%2B%2B&&logoColor=white&style=flat)](https://en.cppreference.com/w/cpp/compiler_support)
[![Platform](https://img.shields.io/static/v1?label=Platform&message=Windows%20x64&color=dimgray&style=flat)](#)

## About

This is a Next-Gen (NG) version of CommonLibF4, which makes it possible to support multiple game versions at the same time, without having to ship multiple builds.
Note that the Next-Gen and VR ports are still in early stages.

The project is based on [alandtse's](https://github.com/alandtse) [CommonLibF4 NG](https://github.com/alandtse/CommonLibF4), with many additions, improvements and fixes.

## Build Dependencies

- [Visual Studio Community 2022 Build Tools 17.12](https://learn.microsoft.com/visualstudio/releases/2022/release-history#evergreen-bootstrappers)
- [mmio](https://github.com/Ryan-rsm-McKenzie/mmio)
- [spdlog](https://github.com/gabime/spdlog)

## Development

- [CMake 3.30](https://cmake.org)
- [vcpkg](https://github.com/microsoft/vcpkg)
  - Create an environmental variable called `VCPKG_ROOT` where the value is the path to your vcpkg installation.

## End User Dependencies

- [F4SE/VR](https://f4se.silverlock.org)
- [Address Library for F4SE Plugins](https://www.nexusmods.com/fallout4/mods/47327)
- [VR Address Library for F4SEVR Plugins](https://www.nexusmods.com/fallout4/mods/64879)

## Development

- [Address Library for F4SE Plugins](https://www.nexusmods.com/fallout4/mods/47327)
- [VR Address Library for F4SEVR Plugins](https://www.nexusmods.com/fallout4/mods/64879)

## Notes

- For info about VR development, see [alandtse's build](https://github.com/alandtse/CommonLibF4)

## Credits

- Thanks to [Ryan McKenzie](https://github.com/Ryan-rsm-McKenzie) for the initial code
- Thanks to [alandtse](https://github.com/alandtse) and [CharmedBaryon](https://github.com/CharmedBaryon) for the [Next-Gen and VR ports](https://github.com/alandtse/CommonLibF4)
- Thanks to maintainers of active forks:
  - [po3](https://github.com/powerof3/CommonLibF4)
  - [shad0wshayd3](https://github.com/shad0wshayd3/CommonLibF4)
