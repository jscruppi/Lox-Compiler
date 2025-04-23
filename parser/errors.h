/*

    Declarations for all error handling functions for the parser

    Author: Joe Scruppi

*/

#ifndef ERRORS_H
#define ERRORS_H

#include "HashSet.h"
#include "lexer/lexer.h"

extern char *yytext;
extern int yylineno;
extern HashSet *symbolTable;
extern int nextToken;

//! Checks if current var has been declared
void checkError100();

//! Checks if current class types has been declared
void checkError101();

//! Checks if var decl is trying to reuse an identifier
void checkError102();

//! Checks for valid literal (string, int, float)
void checkError110();

//! Checks for expected semicolon
void checkError200();

//! Checks for expected curly brace (open + close)
void checkError201();

//! Checks for expected parenthesis (open + close)
void checkError202();

//! Checks for expected operator
void checkError203();

//! Checks for expected logic operator
void checkError204();

//! Checks for expected comma
void checkError205();

//! 'Kitchen Sink' error - used when current error cannot be described by any other error check
void checkError909();

//! Used to display error message to stdout
void throwMessage(const char *message);

#endif