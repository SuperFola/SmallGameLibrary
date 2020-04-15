/**
 * @file Platform.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Defines to identify the running operating system
 * @version 0.1
 * @date 2020-04-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_system_platform
#define sgl_system_platform

#if defined(_WIN32) && !defined(_WIN64)
    #define SGL_SYS_WIN32
#elif defined(_WIN64)
    #define SGL_SYS_WIN64
#endif

#if defined(SGL_SYS_WIN32) || defined(SGL_SYS_WIN64)
    #define SGL_SYS_WINDOWS
#endif

#if (defined(unix) || defined(__unix) || defined(__unix__)) && !defined(__APPLE__)
    #define SGL_SYS_UNIX
#elif defined(__APPLE__)
    #define SGL_SYS_APPLE
#endif

#if defined(__ANDROID__)
    #define SGL_SYS_ANDROID
#endif

#endif