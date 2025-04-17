
# mark all of the source files
file(GLOB_RECURSE SOURCES ./*.c)

# create the parser library
add_library(LOX_PARSER STATIC ${SOURCES})

# link the lexer lib to parser
target_include_directories(LOX_PARSER PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(LOX_PARSER PRIVATE LOX_LEXER)