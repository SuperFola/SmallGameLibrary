# SmallGameLibrary

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

Copyright (c) 2020 Alexandre Plateau (SuperFola). All rights reserved.

This project is distributed under Mozilla Public License 2.0.