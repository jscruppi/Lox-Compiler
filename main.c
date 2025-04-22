
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include "lexer/lexer.h"
#include "parser/parser.h"
//#include "parser/HashSet.h"

// Instantiate global variables
extern FILE *yyin;   // input stream
extern FILE *yyout;  // output stream
extern int yyleng;   // length of current lexeme
extern char *yytext; // text of current lexeme
extern int yylineno; // line number for current lexeme
extern int yylex();  // the generated lexical analyzer

extern HashSet *symbolTable;

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
    //expression(); // Build bottom-up to <expression>
    program();

    if (nextToken != TOK_EOF){
       printf("Still have more to parse in the file\n"); 
       printf("Current lexeme: %s\n", yytext);
    }

    printf("== User Defined symbols ==\n");

    // break here
    for (int x = 0; x < symbolTable->capacity; x++) {
        Node *current = symbolTable->buckets[x];
        while (current != NULL)
        { // loop through the linked list in each bucket
            if (current->key != NULL)
            {
                printf("%s\n", current->key);
            }
            current = current->next; // move to the next node in the chain
        }
    }


    if(contains(symbolTable, "Foo")){
        printf("Contatins\n");
    }

    // free hashset
    freeHashSet(symbolTable);

    return 0;
}
