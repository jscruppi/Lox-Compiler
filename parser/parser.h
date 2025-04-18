/*
    Header file for the parser
    Contains all function definitions

*/

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "HashSet.h"
#include "lexer/lexer.h"

#define BUFF_SIZE 1024

extern HashSet* symbolTable;
extern int nextToken;
extern int yylex(); //generated lexical analyzer
extern char *yytext; //text of current lexeme

//helper functions
void psp();
void output(char* what);

int startOfStatement();
int startOfPrimary();
int startOfExpr();
int isCompareOp();


//function declarations
int lex();
void program();
void declaration();


// Expressions
// Will start developing from the bottom up
void expression();
void primary();
void call();
void unary();
void factor();
void term();
void comparison();
void equality();
void logicAnd();
void logicOr();
void assignment();

//will have to decide if we declare error checks here or other file
//im leaning other file

#endif