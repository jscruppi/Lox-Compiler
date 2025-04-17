
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include "lexer/lexer.h"
#include "parser/parser.h"

// Instantiate global variables
extern FILE *yyin;   // input stream
extern FILE *yyout;  // output stream
extern int yyleng;   // length of current lexeme
extern char *yytext; // text of current lexeme
extern int yylineno; // line number for current lexeme
extern int yylex();  // the generated lexical analyzer

extern int nextToken; // token returned from yylex



int main(int argc, char **argv){
    printf("Dirs are working\n");
    return 0;
}