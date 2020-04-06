/**
 * @file SharedLibrary.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Utility to easily load shared libraries and retrieve their functions
 * @version 0.1
 * @date 2020-04-06
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_sharedlibrary
#define sgl_sharedlibrary

#include <Small/Platform.hpp>

#if defined(SGL_SYS_WINDOWS)
    #include <Windows.h>
#elif defined(SGL_SYS_UNIX) || defined(SGL_SYS_APPLE) || defined(SFL_SYS_ANDROID)
    #include <dlfcn.h>
#else
    #error "Can not identify the platform on which you are running, aborting"
#endif

#include <string>
#include <system_error>
#include <exception>

namespace sgl
{
    /**
     * @brief Class to load / unload shared library on Windows, Linux, MacOS and Android
     * 
     */
    class SharedLibrary
    {
    public:
        /**
         * @brief Construct a new empty Shared Library object
         * 
         */
        SharedLibrary();

        /**
         * @brief Construct a new Shared Library object by loading a shared library from it's relative path
         * @details On Linux, loading a shared libray can fail if it isn't in the PATH, thus you need to prefix the path with './'
         *          to tell it to search in the current folder.
         * 
         * @param path 
         */
        SharedLibrary(const std::string& path);

        /**
         * @brief Destroy the Shared Library object
         * 
         */
        ~SharedLibrary();

        /**
         * @brief Load a shared library from its path
         * @details On Linux, loading a shared libray can fail if it isn't in the PATH, thus you need to prefix the path with './'
         *          to tell it to search in the current folder.
         * 
         * @param path 
         */
        void load(const std::string& path);

        /**
         * @brief Unload the shared library
         * 
         */
        void unload();

        /**
         * @brief Retrieve a function from the shared library, given it's type `T` and its name
         * 
         * @tparam T The type of the function, eg void (*) (int) for a function returning nothing and taking an integer as argument
         * @param procname The name of the function, case sensitive
         * @return T A pointer to the retrieved function
         */
        template <typename T>
        T get(const std::string& procname)
        {
            T funcptr;

#if defined(SGL_SYS_WINDOWS)
            if (NULL == (funcptr = reinterpret_cast<T>(GetProcAddress(m_hInstance, procname.c_str()))))
            {
                throw std::system_error(
                    std::error_code(::GetLastError(), std::system_category())
                    , std::string("Couldn't find ") + procname
                );
            }
#elif defined(SGL_SYS_UNIX) || defined(SGL_SYS_APPLE) || defined(SFL_SYS_ANDROID)
            if (NULL == (funcptr = reinterpret_cast<T>(dlsym(m_hInstance, procname.c_str()))))
            {
                throw std::system_error(
                    std::error_code(errno, std::system_category())
                    , std::string("Couldn't find ") + procname + ", " + std::string(dlerror())
                );
            }
#endif
            return funcptr;
        }
    
    private:
#if defined(SGL_SYS_WINDOWS)
        HINSTANCE m_hInstance;
#elif defined(SGL_SYS_UNIX) || defined(SGL_SYS_APPLE) || defined(SFL_SYS_ANDROID)
        void* m_hInstance;
#endif
        std::string m_path;
        bool m_loaded;
    };
}

#endif  // ge_core_plugin_hpp