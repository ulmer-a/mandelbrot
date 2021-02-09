cmake_minimum_required(VERSION 3.14)

project(FractalRenderer VERSION 1.0)
message(STATUS "${CMAKE_PROJECT_NAME} v${CMAKE_PROJECT_VERSION}")

find_package(OpenGL REQUIRED)

# Default build type: Release
if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release")
endif()

option(DEBUG "enable debug mode" OFF)
if(DEBUG)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message(STATUS "engine: building ${CMAKE_BUILD_TYPE} configuration")

# Use C++20 for the entire project
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Platform definitions
set(OS_NAME "${CMAKE_SYSTEM_NAME}")
message(STATUS "engine: building for platform ${CMAKE_SYSTEM_NAME}")
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    add_compile_definitions(ENGINE_OS_LINUX=1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    add_compile_definitions(ENGINE_OS_WINDOWS=1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    add_compile_definitions(ENGINE_OS_MAC_OS=1)
endif()


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/glew)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/cmdline)

file(GLOB FRAC_HEADERS "src/*.h")
file(GLOB FRAC_SOURCES "src/*.cpp")
add_executable(fractal ${FRAC_HEADERS} ${FRAC_SOURCES})

target_compile_definitions(fractal PRIVATE
    $<$<CONFIG:Debug>:FRACTAL_DEBUG>
    FRACTAL_IMPL
)

target_link_libraries(fractal cmdline glfw libglew_static)
target_include_directories(fractal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cmdline/source
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glew/include
)
