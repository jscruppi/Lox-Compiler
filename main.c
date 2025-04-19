
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

    // Set the input stream
    if (argc > 1) {
        printf("INFO: Using the %s file for input\n", argv[1]);
        yyin = fopen(argv[1], "r"); 
    }
    else {
        printf("INFO: Using stdin for input\n");
        yyin = stdin;
    }
  
    if (!yyin) {
        printf("ERROR: input file not found\n");
        return EXIT_FAILURE;
    }

    // set output stream
    yyout = stdout;

    // get first token
    nextToken = yylex();

    // start the parser
    // Process the expected production
    //program();  
    equality(); // Build bottom-up to <expression>

    if (nextToken != TOK_EOF)
       printf("Still have more to parse in the file\n"); 
    

    return 0;
}
