/**
 * @file Config.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_scripting_config
#define sgl_small_scripting_config

#include <string>

namespace sgl::Scripting
{
    /**
     * @brief Host the scripting engine configuration
     * 
     */
    struct Config
    {
        std::string scriptsDirectory;    //< Game scripts directory
        std::string compiledScriptsDir;  //< Directory where the compiled scripts should be put
        std::string arkscriptLibDir;     //< Path to the ArkScript standard library
    };
}

#endif