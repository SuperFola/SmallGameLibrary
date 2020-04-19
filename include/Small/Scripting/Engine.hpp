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
    constexpr char* ArkScriptLibDir = "assets/arkscript/lib";

    /**
     * @brief Compile an ArkScript file to ArkScript bytecode
     * 
     * @param file Path to the ArkScript file to compile
     * @param output Output path where the bytecode should be saved (same filename, the extension becomes .arkc instead of .ark)
     * @return true If the file was successfuly compiled
     * @return false Otherwise
     */
    bool compileScript(const std::string& file, const std::string& output);
}

#endif