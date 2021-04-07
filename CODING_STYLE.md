# File name convention

All files (and folders) must be named following Pascal case.

## Header guards

Should be written as follows: `SMALL_FOLDER1_FOLDER2_FILE_HPP`.

Eg: a file `include/Something/Sub/Hello.hpp` will have a header guard named `SOMETHING_SUB_HELLO_HPP`.

# C++ code

## namespaces

The top namespace is named `sgl`. Every other sub-namespace should be named following Pascal case, except for the `sgl::internal` namesapce.

## vector

Prefer using `sf::Vector2i` when possible, instead of `sf::Vector2u`, to avoid a lot of casts.

## inheritance

If a method of a given class should be public, but the class can be derived from, and this method is a getter / setter for all the children, then it should be marked as `final`.

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