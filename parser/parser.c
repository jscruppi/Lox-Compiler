/*
    Function definitions for the parser
*/

#ifdef _MSC_VER
#define _CRT_SERCURE_NO_WARNINGS
#endif

#include "parser.h"
#include "lexer/lexer.h"
#include <string.h>
#include <assert.h>

int nextToken = 0;
char* idName;
char* idType;

static int print_debug = 1; //flag used to print out the parsing for debugging

static int level = 0; //tells us what level of parse tree we are in
HashSet* symbolTable = NULL; //will have to initalize in the main function

// Indent to reveal tree structure
// TODO : make a method that does this locally 
// return a pointer to a printf statement is mem leak
// use part 3's version where method prints the spaces instead
void psp() { 
    for(int i = 0; i < level; i++)
        printf("|  ");
}

//reports the current lexeme found
void output(char* what){
    psp();
    printf(" found |%s| %s\n", yytext, what);
}

//checks if current token is statement
int startOfStatement(){
    return nextToken == TOK_FOR || nextToken == TOK_IF || nextToken == TOK_PRINT || 
    nextToken == TOK_RETURN || nextToken == TOK_WHILE || nextToken == TOK_OPENBRACE;
    //TODO: need to check for first of expression
}

//checks if current token is declaration
int startOfDec(){
    return nextToken == TOK_CLASS || nextToken == TOK_FUN || nextToken == TOK_VAR || startOfStatement();
}

int lex(){
    char* token_str;
    
    //move parser
    nextToken = yylex();

    //determine the specific lexeme
    switch(nextToken){
        case TOK_CLASS:             token_str = (char*)"CLASS"; break;
        case TOK_ELSE:              token_str = (char*)"ELSE"; break;
        case TOK_FALSE:             token_str = (char*)"FALSE"; break;
        case TOK_FOR:               token_str = (char*)"FOR"; break;
        case TOK_FUN:               token_str = (char*)"FUN"; break;
        case TOK_IF:                token_str = (char*)"IF"; break;
        case TOK_NIL:               token_str = (char*)"NIL"; break;
        case TOK_PRINT:             token_str = (char*)"PRINT"; break;
        case TOK_RETURN:            token_str = (char*)"RETURN"; break;
        case TOK_SUPER:             token_str = (char*)"SUPER"; break;
        case TOK_THIS:              token_str = (char*)"THIS"; break;
        case TOK_TRUE:              token_str = (char*)"TRUE"; break;
        case TOK_VAR:               token_str = (char*)"VAR"; break;
        case TOK_WHILE:             token_str = (char*)"WHILE"; break;

        case TOK_OPENPAREN:         token_str = (char*)"OPENPAREN"; break;
        case TOK_CLOSEPAREN:        token_str = (char*)"CLOSEPAREN"; break;
        case TOK_OPENBRACE:         token_str = (char*)"OPENBRACE"; break;
        case TOK_CLOSEBRACE:        token_str = (char*)"CLOSEBRACE"; break;
        case TOK_SEMICOLON:         token_str = (char*)"SEMICOLON"; break;
        case TOK_COMMA:             token_str = (char*)"COMMA"; break;
        case TOK_DOT:               token_str = (char*)"DOT"; break;
        case TOK_OPENBRACK:         token_str = (char*)"OPENBRACK"; break;
        case TOK_CLOSEBRACK:        token_str = (char*)"CLOSEBRACK"; break;
        case TOK_COLON:             token_str = (char*)"COLON"; break;
        
        case TOK_PLUS:              token_str = (char*)"PLUS"; break;
        case TOK_MINUS:             token_str = (char*)"MINUS"; break;
        case TOK_MULT:              token_str = (char*)"MULT"; break;
        case TOK_DIV:               token_str = (char*)"DIV"; break;
        case TOK_ASSIGN:            token_str = (char*)"ASSIGN"; break;
        case TOK_EQUAL:             token_str = (char*)"EQUAL"; break;
        case TOK_NOTEQUAL:          token_str = (char*)"NOTEQUAL"; break;
        case TOK_LESS:              token_str = (char*)"LESS"; break;
        case TOK_GREATER:           token_str = (char*)"GREATER"; break;
        case TOK_LESSEQUAL:         token_str = (char*)"LESSEQUAL"; break;
        case TOK_GREATEQUAL:        token_str = (char*)"GREATEQUAL"; break;
        case TOK_NOT:               token_str = (char*)"NOT"; break;
        case TOK_AND:               token_str = (char*)"AND"; break;
        case TOK_OR:                token_str = (char*)"OR"; break;

        case TOK_STRING:            token_str = (char*)"STRING"; break;
        case TOK_INT:               token_str = (char*)"INT"; break;
        case TOK_FLOAT:             token_str = (char*)"FLOAT"; break;
        case TOK_IDENT:             token_str = (char*)"IDENT"; break;

        case TOK_EOF:               token_str = (char*)"==EOF==";break;

        default:                    
            printf("Token: |%s|\n", yytext);
            //error msg here 
    }

    return nextToken;
}

void program(){

    //if(print_debug)output("PROGRAM");
    //lex();
    
    if(print_debug){psp(); printf("enter <program>\n");}
    level++;

    //any # of declarations
    while(startOfDec() && nextToken != TOK_EOF){
        if(print_debug)output("Declaration");
        //lex();
        declaration();
    }

    //if(print_debug)output("EOF");
    //lex(); // not sure if we need to move it after this

    level--;
    if(print_debug){psp(); printf("exit <program>\n");}
}

void declaration(){

    if(print_debug){psp(); printf("enter <Declaration>\n");}
    level++;

    //determine the specific declaration
    if(nextToken == TOK_CLASS){
        if(print_debug)output("Class");
        lex();
        //classDec();
    }
    else if(nextToken == TOK_FUN){
        if(print_debug)output("Function");
        lex();
        //funDec();
    }
    else if(nextToken == TOK_VAR){
        if(print_debug)output("Variable");
        lex();
        //varDec();
    }
    else if(startOfStatement()){
        if(print_debug)output("Statement");
        lex();
        //statement();
    }
    else{
        //need some sort of error msg here
    }

    level--;
    if(print_debug){psp(); printf("exit <Declaration>\n");}
}

void expression(){}

void primary(){

    if(print_debug){psp(); printf("enter <primary>\n");}
    level++;

    switch(nextToken){

        case TOK_TRUE:
            if(print_debug)output("true");
            lex();
            break;

        case TOK_FALSE:
            if(print_debug)output("false");
            lex();
            break;

        case TOK_NIL:
            if(print_debug)output("nil");
            lex();
            break;

        case TOK_THIS:
            if(print_debug)output("this");
            lex();
            break;

        case TOK_INT:
            if(print_debug)output("INTLIT");
            lex();
            break;

        case TOK_FLOAT:
            if(print_debug)output("FLOATLIT");
            lex();
            break;

        case TOK_IDENT:
            if(print_debug)output("IDENTIFIER");
            lex();
            break;

        case TOK_OPENPAREN:
            if(print_debug)output("open-paren");
            lex();
            if(print_debug)output("expression");
            expression();
            if(print_debug)output("close-paren");
            lex();
            break;

        case TOK_SUPER:
            if(print_debug)output("super");
            lex();
            if(print_debug)output(".");
            lex();
            if(print_debug)output("IDENTIFIER");
            lex();
            break;

        default:
            printf("In primary -- found incorrect token\n");
            exit(EXIT_FAILURE);
            break;
    } 

    level--;
    if(print_debug){psp(); printf("exit <primary>\n");}
}



