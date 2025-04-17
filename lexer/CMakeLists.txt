
#find flex package
find_package(FLEX REQUIRED)

#compile flex target
flex_target(LEXER rules.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)

#this should add header file dependency
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#create flex obj file
add_library(lexer_obj OBJECT ${FLEX_LEXER_OUTPUTS})

#create final exectuable
add_library(LOX_LEXER STATIC
    $<TARGET_OBJECTS:lexer_obj>
    )

target_include_directories(LOX_LEXER PUBLIC ${CMAKE_CURRENT_SORUCE_DIR})