cmake_minimum_required(VERSION 3.10)
project(lox_lexer)

#find flex package
find_package(FLEX REQUIRED)

#compile flex target
flex_target(LEXER rules.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)

#this should add header file dependency
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#create flex obj file
add_library(lexer_obj OBJECT ${FLEX_LEXER_OUTPUTS})

#create dirver obj
add_library(driver_obj OBJECT driver.c)

#create final exectuable
add_executable(lox_lex   
    $<TARGET_OBJECTS:driver_obj>
    $<TARGET_OBJECTS:lexer_obj>
    )