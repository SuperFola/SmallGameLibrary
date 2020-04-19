cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0074 NEW)

project(Thirdparty)

# ArkScript
set(ARK_BUILD_EXE       OFF)
set(ARK_BUILD_BENCHMARK OFF)
set(ARK_BUILD_MODULES   OFF)
set(ARK_ENABLE_SYSTEM   OFF)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/arkscript)

file(GLOB_RECURSE all_sources
    # imgui
    ${CMAKE_CURRENT_LIST_DIR}/imgui/*.c
    ${CMAKE_CURRENT_LIST_DIR}/imgui/*.cpp
)

set(THIRDPARTY_SOURCES
    ${all_sources}

    PARENT_SCOPE
)

set(THIRDPARTY_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/imgui
    ${CMAKE_CURRENT_LIST_DIR}/termcolor
    ${CMAKE_CURRENT_LIST_DIR}/entt/src
    ${CMAKE_CURRENT_LIST_DIR}/arkscript/include

    PARENT_SCOPE
)

set(THIRDPARTY_LIBS
    ArkReactor

    PARENT_SCOPE
)