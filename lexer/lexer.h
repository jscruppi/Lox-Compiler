/*
    Define all the tokens and their associated values
    To be used in the Lox compiler project

    Author: Joe Scruppi

*/

#ifndef LEXER_H
#define LEXER_H

//keywords
#define TOK_CLASS       1001
#define TOK_ELSE        1002
#define TOK_FALSE       1003
#define TOK_FOR         1004
#define TOK_FUN         1005
#define TOK_IF          1006
#define TOK_NIL         1007
#define TOK_OR          1008
#define TOK_PRINT       1009
#define TOK_RETURN      1010
#define TOK_SUPER       1011
#define TOK_THIS        1012
#define TOK_TRUE        1013
#define TOK_VAR         1014
#define TOK_WHILE       1015

//puncuation
#define TOK_OPENPAREN   2000
#define TOK_CLOSEPAREN  2001
#define TOK_OPENBRACE   2002
#define TOK_CLOSEBRACE  2003
#define TOK_SEMICOLON   2004
#define TOK_COMMA       2005
#define TOK_DOT         2006
#define TOK_OPENBRACK   2007
#define TOK_CLOSEBRACK  2008
#define TOK_COLON       2009

//operators
#define TOK_PLUS        3000
#define TOK_MINUS       3001
#define TOK_MULT        3002
#define TOK_DIV         3003
#define TOK_ASSIGN      3004
#define TOK_EQUAL       3005
#define TOK_NOTEQUAL    3006
#define TOK_LESS        3007
#define TOK_GREATER     3008
#define TOK_LESSEQUAL   3009
#define TOK_GREATEQUAL  3010
#define TOK_NOT         3011
#define TOK_AND         3012
#define TOK_OR          3013

//abstractions
#define TOK_STRING      4000
#define TOK_INT         4001
#define TOK_FLOAT       4002
#define TOK_IDENT       4003
#define TOK_EOF         4004
#define TOK_UNKNOWN     4005
#define TOK_INVALIDLIT  4006

#endif