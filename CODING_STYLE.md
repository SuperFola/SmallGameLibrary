# File name convention

All files (and folders) must be named following Pascal case.

## Header guards

Should be written as follows: `sgl_folder1_folder2_file`.

Eg: a file `include/Something/Sub/Hello.hpp` will have a header guard named `sgl_something_sub_hello`.

# C++ code

## namespaces

The top namespace is named `sgl`. Every other sub-namespace should be named following Pascal case, except for the `sgl::internal` namesapce.

# Documentation

Every class, method, function and constant must be documented following doxygen convention.

Files must also have a top comment following doxygen convention. Example for `include/Small/Core/Application.hpp`:
```cpp
/**
 * @file Application.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Define the application hosting the scenes for the game
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
```

The version number should be increased following [**SemVer**](https://semver.org/) convention, each time a file is modified. Also the `@author` should be updated to add your name if you contributed to this file (**do not** remove the other author's names).