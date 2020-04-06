#ifndef sgl_platform
#define sgl_platform

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