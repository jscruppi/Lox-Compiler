/*

    Definitions for all error handling functions for the parser

    Autho: Joe Scruppi

*/

#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

void throwMessage(const char* message){
    printf("Error [Line #%d]\n", &yylineno);
    printf("\t%s\n",message);
    exit(EXIT_FAILURE);
}

void checkError100(){
    if(!contains(symbolTable,  yytext)){
        throwMessage("Variable has not been declared");
    }
}

void checkError101(){
    if(!contains(symbolTable, yytext)){
        throwMessage("Class has not been declared");
    }
}

void checkError102(){
    if(contains(symbolTable, yytext)){
        throwMessage("Identifier is used more than once");
    }
}

void checkError110(){
    throwMessage("Invalid literal");
}

void checkError200(){
    if(nextToken != TOK_SEMICOLON){
        throwMessage("Expected ;");
    }
}

void checkError201(){
    if(nextToken != TOK_OPENBRACE && nextToken != TOK_CLOSEBRACE){
        throwMessage("Expected {}");
    }
}

void checkError202(){
    if(nextToken != TOK_OPENPAREN && nextToken != TOK_CLOSEPAREN){
        throwMessage("Expected ()");
    }
}

void checkError203(){
    if(nextToken != TOK_LESS && nextToken != TOK_ASSIGN && nextToken != TOK_MINUS
    && nextToken != TOK_PLUS && nextToken != TOK_DIV && nextToken != TOK_MULT
    && nextToken != TOK_NOT && nextToken != TOK_DOT)
        throwMessage("Expected operator");
}

void checkError204(){
    if(nextToken != TOK_AND && nextToken != TOK_OR && nextToken != TOK_NOTEQUAL
    && nextToken != TOK_EQUAL && nextToken != TOK_LESS && nextToken != TOK_LESSEQUAL
    && nextToken != TOK_GREATER && nextToken != TOK_GREATEQUAL)
        throwMessage("[Invalid expression] Expected logical operator");
}

void checkError205(){
    if(nextToken != TOK_COMMA){
        throwMessage("Expected ,");
    }
}

void checkError909(){
    throwMessage("Unrecoverable Error");
}