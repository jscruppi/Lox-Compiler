# CMAKE file for compiler

cmake_minimum_required(VERSION 3.10)
project(lox_compiler)

# add other libraries
add_subdirectory(lexer)

# create main executable
# will be changing as tests for
# the project evolve
add_executable(test_exec driver.c)
target_link_libraries(test_exec LOX_LEXER)