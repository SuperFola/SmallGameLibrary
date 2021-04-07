/**
 * @file FileSystem.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Useful functionalities related to the filesystem
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SMALL_SYSTEM_FILESYSTEM_HPP
#define SMALL_SYSTEM_FILESYSTEM_HPP

#include <string>
#include <vector>

namespace sgl::System
{
    /**
     * @brief List all entries in a given directory
     * 
     * @param directory Path to the directory
     * @return std::vector<std::string> 
     */
    std::vector<std::string> listDir(const std::string& directory);
}

#endif
