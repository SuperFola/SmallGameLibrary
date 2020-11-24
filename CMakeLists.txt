cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0074 NEW)

project(SGL)  # small game library

# clang isn't detected by cmake currently
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_COMPILER_IS_CLANG ON)
endif()

# -fPIE because we are building a library
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# search for needed libraries
find_package(SFML 2.5 COMPONENTS system graphics window audio network REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

# add thirdparties
add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty)
set(BUILD_STATIC_LIBS On)
add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty/glm)

# search for source files
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp)

message(STATUS ${THIRDPARTY_INCLUDES})

# building the library
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${THIRDPARTY_SOURCES})

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    sfml-system sfml-graphics sfml-window sfml-audio sfml-network glm::glm_static
    ${THIRDPARTY_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENGL_LIBRARIES}
)

# include headers
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${THIRDPARTY_INCLUDES}
    ${OPENGL_INCLUDE_DIRS}
)

# require C++17
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)