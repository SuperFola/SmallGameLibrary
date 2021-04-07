# SmallGameLibrary ![Latest version](https://img.shields.io/github/v/tag/superfola/smallgamelibrary?label=version&include_prereleases&style=for-the-badge)

![Code size](https://img.shields.io/github/languages/code-size/SuperFola/SmallGameLibrary?style=for-the-badge&logo=github)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/SuperFola/SmallGameLibrary/CI?logo=cmake&style=for-the-badge)

A C++17 small game library relying on SFML 2.5.x.

# Dependencies

* CMake >= 3.10
* C++17 compiler
* SFML >= 2.5

# Examples

Examples are provided in the `examples/` folder, and can be built right there, they automatically add the SmallGameLibrary as a dependency.

# Build instructions

```shell
~/SGL$ cmake . -Bbuild -DCMAKE_BUILD_TYPE=Release
~/SGL$ cmake --build build --config Release
```

# Copyright and License information

Copyright (c) 2020-2021 Alexandre Plateau (SuperFola). All rights reserved.

This project is distributed under Mozilla Public License 2.0.