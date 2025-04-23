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

extern HashSet* symbolTable; //! Lists that stores users' created identifiers
extern int nextToken; //! The current token return by flex
extern char *yytext; //! Text of current lexeme
//! Generated lexical analyzer
extern int yylex(); 

////
// helper functions
////

//! Used for debugging - sets indent based on level(depth) of call
void psp();
//! Used for debugging - outputs what we should expect to parse and compares to what is actually parsed
void output(char* what);

//! Returns if lexeme begins a statement
int startOfStatement();
//! Returns if lexeme begins a primary
int startOfPrimary();
//! Returns if lexeme begins a expression
int startOfExpr();
//! Returns if lexeme begins a declaration
int startOfDec();
//! Returns if lexeme is a comparator operator
int isCompareOp();

////
// function declarations
////

//! Advances the lexer by 1
int lex();

//! Parses the rule 'program'
void program();
//! Parses the rule 'declaration'
void declaration();
//! Parses the rule 'class_decl'
void classDecl();
//! Parses the rule 'fun_decl'
void funDecl();
//! Parses the rule 'var_decl'
void varDecl();
//! Parses the rule 'function'.
/* Function is not an explicit grammar rule defined by LOX
    Instead it is used to make the code/grammar more readable as
    The segment is used in different explicit grammar rules
*/
void function();

////
// statement declarations
////

//! Parses the rule 'statement'
void statement();
//! Parses the rule 'expr_stmt'
void exprStmt();
//! Parses the rule 'for_stmt'
void forStmt();
//! Parses the rule 'if_stmt'
void ifStmt();
//! Parses the rule 'print_stmt'
void printStmt();
//! Parses the rule 'return_stmt'
void returnStmt();
//! Parses the rule 'while_stmt'
void whileStmt();
//! Parses the rule 'block'
void block();

////
// Expressions
////

//! Parses the rule 'expression'
void expression();
//! Parses the rule 'primary'
void primary();
//! Parses the rule 'call'
void call();
//! Parses the rule 'unary'
void unary();
//! Parses the rule 'factor'
void factor();
//! Parses the rule 'term'
void term();
//! Parses the rule 'comparison'
void comparison();
//! Parses the rule 'equality'
void equality();
//! Parses the rule 'logic_and'
void logicAnd();
//! Parses the rule 'logic_or'
void logicOr();
//! Parses the rule 'assignment'
void assignment();

#endif