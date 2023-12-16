cmake_minimum_required(VERSION 3.5)
project(ifpr_provas_2023 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_C_VERSION 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

set(ifpr_provas_2023_CompilerOptions ${ifpr_provas_2023_CompilerOptions}
    -Werror
    -Wall
    -Wextra
    -Wshadow
    -Wcast-align
    -Wunused
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
)

include(static_analyzers)

#
# find_package(package CONFIG REQUIRED)
# . . .
#
# set(ifpr_provas_2023_ExternalLibraries)
#

add_subdirectory(ifpr_provas_2023)
