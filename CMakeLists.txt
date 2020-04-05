cmake_minimum_required(VERSION 3.10)

project(SGL)  # small game library

# clang isn't detected by cmake currently
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_COMPILER_IS_CLANG ON)
endif()

# -fPIE because we are building a library
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# search for needed libraries
find_package(SFML 2.5 COMPONENTS system graphics window audio network REQUIRED)
find_package(Threads)

# search for source files
file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/source/*.cpp
    ${PROJECT_SOURCE_DIR}/thirdparty/*.c
    ${PROJECT_SOURCE_DIR}/thirdparty/*.cpp
)

# building the library
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    sfml-system sfml-graphics sfml-window sfml-audio sfml-network
    ${CMAKE_THREAD_LIBS_INIT}
)

# include headers
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/thirdparty
)

# require C++17
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)