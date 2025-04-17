/*
    Header file for the parser
    Contains all function definitions

*/

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "HashSet.h"
//#include "lexer/lexer.h"

#define BUFF_SIZE 1024

extern HashSet* symbolTable;
extern int nextToken;
extern int yylex(); //generated lexical analyzer
extern char* yytext(); //text of current lexeme

//helper functions
char* psp(void);
int appendChar(char* str, const char c, size_t buffer_size);
void output(char* what);

int startOfStatement();


//function declarations
int lex();
void program();
void declaration();

//will have to decide if we declare error checks here or other file
//im leaning other file

#endif