# CMAKE file for compiler

cmake_minimum_required(VERSION 3.10)
project(lox_compiler)

# set to debug mode
set(CMAKE_BUILD_TYPE Debug)

# so lsp can find headers and such
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add other libraries
add_subdirectory(lexer)
add_subdirectory(parser)

# create main executable
# will be changing as tests for
# the project evolve
add_executable(test_exec main.c)

target_include_directories(test_exec PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test_exec PRIVATE LOX_LEXER LOX_PARSER)
