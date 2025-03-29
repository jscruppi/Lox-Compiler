/*
    Main file for the lexer
    Will be doing the lexical anaylisis with help from flex
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include "lexer.h"

// Instantiate global variables
extern FILE *yyin;   // input stream
extern FILE *yyout;  // output stream
extern int yyleng;   // length of current lexeme
extern char *yytext; // text of current lexeme
extern int yylineno; // line number for current lexeme
extern int yylex();  // the generated lexical analyzer

int main(int argc, char* argv[]){
    int token;
    char* token_str;

    //set input stream
    if(argc > 1){
        printf("INFO: Using the %s file for the input\n", argv[1]);
        yyin = fopen(argv[1], "r");
    }
    else{
        printf("Using stdin for input\n");
        yyin = stdin;
    }

    if(!yyin){
        printf("ERROR: input file not found\n");
        return(-1);
    }

    yyout = stdout; //output stream set

    //lexical parsing:
    token = yylex();
    while(1){

        if(token == TOK_EOF){
            printf("<<Found end of file>>\n");
            break;
        }

        //determine our specific lexeme
        switch(token){
            case TOK_CLASS:             token_str = (char*)"TOK_CLASS"; break;
            case TOK_ELSE:              token_str = (char*)"TOK_ELSE"; break;
            case TOK_FALSE:             token_str = (char*)"TOK_FALSE"; break;
            case TOK_FOR:               token_str = (char*)"TOK_FOR"; break;
            case TOK_FUN:               token_str = (char*)"TOK_FUN"; break;
            case TOK_IF:                token_str = (char*)"TOK_IF"; break;
            case TOK_NIL:               token_str = (char*)"TOK_NIL"; break;
            case TOK_PRINT:             token_str = (char*)"TOK_PRINT"; break;
            case TOK_RETURN:            token_str = (char*)"TOK_RETURN"; break;
            case TOK_SUPER:             token_str = (char*)"TOK_SUPER"; break;
            case TOK_THIS:              token_str = (char*)"TOK_THIS"; break;
            case TOK_TRUE:              token_str = (char*)"TOK_TRUE"; break;
            case TOK_VAR:               token_str = (char*)"TOK_VAR"; break;
            case TOK_WHILE:             token_str = (char*)"TOK_WHILE"; break;

            case TOK_OPENPAREN:         token_str = (char*)"TOK_OPENPAREN"; break;
            case TOK_CLOSEPAREN:        token_str = (char*)"TOK_CLOSEPAREN"; break;
            case TOK_OPENBRACE:         token_str = (char*)"TOK_OPENBRACE"; break;
            case TOK_CLOSEBRACE:        token_str = (char*)"TOK_CLOSEBRACE"; break;
            case TOK_SEMICOLON:         token_str = (char*)"TOK_SEMICOLON"; break;
            case TOK_COMMA:             token_str = (char*)"TOK_SEMICOLON"; break;
            case TOK_DOT:               token_str = (char*)"TOK_DOT"; break;
            case TOK_OPENBRACK:         token_str = (char*)"TOK_OPENBRACK"; break;
            case TOK_CLOSEBRACK:        token_str = (char*)"TOK_CLOSEBRACK"; break;
            case TOK_COLON:             token_str = (char*)"TOK_COLON"; break;
            
            case TOK_PLUS:              token_str = (char*)"TOK_PLUS"; break;
            case TOK_MINUS:             token_str = (char*)"TOK_MINUS"; break;
            case TOK_MULT:              token_str = (char*)"TOK_MULT"; break;
            case TOK_DIV:               token_str = (char*)"TOK_DIV"; break;
            case TOK_ASSIGN:            token_str = (char*)"TOK_ASSIGN"; break;
            case TOK_EQUAL:             token_str = (char*)"TOK_EQUAL"; break;
            case TOK_NOTEQUAL:          token_str = (char*)"TOK_NOTEQUAL"; break;
            case TOK_LESS:              token_str = (char*)"TOK_LESS"; break;
            case TOK_GREATER:           token_str = (char*)"TOK_GREATER"; break;
            case TOK_LESSEQUAL:         token_str = (char*)"TOK_LESSEQUAL"; break;
            case TOK_GREATEQUAL:        token_str = (char*)"TOK_GREATEQUAL"; break;
            case TOK_NOT:               token_str = (char*)"TOK_NOT"; break;
            case TOK_AND:               token_str = (char*)"TOK_AND"; break;
            case TOK_OR:                token_str = (char*)"TOK_OR"; break;

            case TOK_STRING:            token_str = (char*)"TOK_STRING"; break;
            case TOK_INT:               token_str = (char*)"TOK_INT"; break;
            case TOK_FLOAT:             token_str = (char*)"TOK_FLOAT"; break;
            case TOK_IDENT:             token_str = (char*)"TOK_IDENT"; break;

            default:                    token_str =  (char*)"<<unmapped token name>>";
        }

        //show what was found
        fprintf(yyout, "line %d, lexeme: |%s|, length: %d, token %s\n",
                yylineno, yytext, yyleng, token_str);
        
        //check for error
        if(token == TOK_UNKNOWN){
            fprintf(yyout, "! ERROR: unknown token\n");
            return(-1);
        }

        token = yylex(); //get next token
        
    }

    return 0;
}