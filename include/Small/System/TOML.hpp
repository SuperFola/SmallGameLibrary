/**
 * @file TOML.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Include toml.hpp and add a few things to make it work with one include (the lib is relying on other files, not included)
 * @version 0.1
 * @date 2020-04-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_system_toml
#define sgl_small_system_toml

#include <fstream>  // needed for toml::parse_file
#include <toml.hpp>
#include <string_view>

/**
 * @brief Import the string suffix ""sv
 * @details It's needed by toml++ to perform things like:
 * @code
 * auto tbl = toml::parse("enabled = true"sv);
 * @endcode
 * 
 */
using namespace std::string_view_literals;

#endif