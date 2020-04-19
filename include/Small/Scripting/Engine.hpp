/**
 * @file Engine.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Easing the use of ArkScript (compiling scripts ahead of time, loading them)
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_scripting_engine
#define sgl_small_scripting_engine

#include <Ark/Ark.hpp>

#include <string>

namespace sgl::Scripting
{
    /**
     * @brief Compile an ArkScript file to ArkScript bytecode
     * 
     * @param file Path to the ArkScript file to compile
     * @param output Output path where the bytecode should be saved (same filename, the extension becomes .arkc instead of .ark)
     * @param arkscriptLibDir Path to the ArkScript standard library
     * @return true If the file was successfuly compiled
     * @return false Otherwise
     */
    bool compileScript(const std::string& file, const std::string& output, const std::string& arkscriptLibDir);

    /**
     * @brief Compile all scripts in a given directory, and put their output in another directory
     * 
     * @param path Path where the scripts lie
     * @param outputDir Path to put the compiled scripts
     * @param arkscriptLibDir Path to the ArkScript standard library
     * @return int Number of scripts successfully compiled
     */
    int compileAllScriptsIn(const std::string& path, const std::string& outputDir, const std::string& arkscriptLibDir);
}

#endif