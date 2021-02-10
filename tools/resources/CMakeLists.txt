cmake_minimum_required(VERSION 3.14)

file(GLOB RC_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB RC_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(rc ${RC_HEADERS} ${RC_SOURCES})

target_compile_definitions(rc PRIVATE
    $<$<CONFIG:Debug>:FRACTAL_DEBUG>
)

target_link_libraries(rc cmdline)
target_include_directories(rc PUBLIC
    ${PROJECT_SOURCE_DIR}/lib/cmdline/source
)
