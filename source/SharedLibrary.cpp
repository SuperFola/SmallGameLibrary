#include <Small/SharedLibrary.hpp>

#include <sstream>
#include <iomanip>
#include <iostream>

namespace sgl
{
    SharedLibrary::SharedLibrary() :
        m_hInstance(NULL)
        , m_path("")
        , m_loaded(false)
    {}

    SharedLibrary::SharedLibrary(const std::string& path) :
        m_hInstance(NULL)
        , m_path(path)
        , m_loaded(false)
    {
        load(m_path);
    }

    SharedLibrary::~SharedLibrary()
    {
        unload();
    }

    void SharedLibrary::load(const std::string& path)
    {
        if (m_loaded)
            unload();
        m_path = path;
        
#if defined(SGL_SYS_WINDOWS)
        if (NULL == (m_hInstance = LoadLibrary(m_path.c_str())))
        {
            throw std::system_error(
                std::error_code(::GetLastError(), std::system_category())
                , "Couldn't load the library at " + path
            );
        }
#elif defined(SGL_SYS_UNIX) || defined(SGL_SYS_APPLE) || defined(SFL_SYS_ANDROID)
        if (NULL == (m_hInstance = dlopen(m_path.c_str(), RTLD_NOW | RTLD_GLOBAL)))
        {
            throw std::system_error(
                std::error_code(errno, std::system_category())
                , "Couldn't load the library at " + path + ", " + std::string(dlerror())
            );
        }
#endif
        m_loaded = true;
    }

    void SharedLibrary::unload()
    {
        if (m_loaded)
        {
#if defined(SGL_SYS_WINDOWS)
            FreeLibrary(m_hInstance);
#elif defined(SGL_SYS_UNIX) || defined(SGL_SYS_APPLE) || defined(SFL_SYS_ANDROID)
            dlclose(m_hInstance);
#endif
        }
    }
}