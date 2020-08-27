cmake_minimum_required(VERSION 3.10)

project(Disney)

# do not show console in release
if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

# SGL
add_subdirectory(${PROJECT_SOURCE_DIR}/../../ ${PROJECT_SOURCE_DIR}/SGL)

# search for source files
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp)

# include headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# building the project
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC SGL ArkReactor)

# require C++17
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)