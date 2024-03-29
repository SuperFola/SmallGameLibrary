/**
 * @file All.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Include the needed files to start a project using the library
 * @version 0.5
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SMALL_ALL_HPP
#define SMALL_ALL_HPP

/**
 * @brief Base namespace for the library.
 * 
 */
namespace sgl {}

/**
 * @brief Contain internal code, which shouldn't be directly used by the end user
 * @details Documented for contributors only
 * 
 */
namespace sgl::internal {}

#include <Small/Core.hpp>
#include <Small/Graphics.hpp>
#include <Small/System.hpp>
#include <Small/Scenes.hpp>
#include <Small/Widgets.hpp>
#include <Small/Scripting.hpp>
#include <Small/GameObjects.hpp>

#endif
