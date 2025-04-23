/*
    Function definitions for the parser
*/

#ifdef _MSC_VER
#define _CRT_SERCURE_NO_WARNINGS
#endif

#include "parser.h"
#include "lexer/lexer.h"
#include "errors.h"
#include <string.h>
#include <assert.h>

int nextToken = 0;
char* idName;
char* idType;

static int print_debug = 0; //flag used to print out the parsing for debugging

static int level = 0; //tells us what level of parse tree we are in
HashSet* symbolTable = NULL; //will have to initalize in the main function

// prints out spaces depending on the level of parse
// used for debugging purposes
void psp() { 
    for(int i = 0; i < level; i++)
        printf("|  ");
}

//reports the current lexeme found
void output(char* what){
    psp();
    printf("found |%s| %s\n", yytext, what);
}

//checks if current token is statement
int startOfStatement(){
    return nextToken == TOK_FOR || nextToken == TOK_IF || nextToken == TOK_PRINT || 
    nextToken == TOK_RETURN || nextToken == TOK_WHILE || nextToken == TOK_OPENBRACE
    || startOfExpr();
}

int startOfExpr(){
    return startOfPrimary() || nextToken == TOK_MINUS || nextToken == TOK_NOT;
}

int startOfPrimary(){
    return nextToken == TOK_TRUE || nextToken == TOK_FALSE || nextToken == TOK_NIL || nextToken == TOK_THIS ||
    nextToken == TOK_INT || nextToken == TOK_FLOAT || nextToken == TOK_STRING || nextToken == TOK_IDENT || nextToken == TOK_OPENPAREN ||
    nextToken == TOK_SUPER;
}

//checks if current token is declaration
int startOfDec(){
    return nextToken == TOK_CLASS || nextToken == TOK_FUN || nextToken == TOK_VAR || startOfStatement();
}

int isCompareOp(){
    return nextToken == TOK_GREATER || nextToken == TOK_GREATEQUAL 
    || nextToken == TOK_LESS || nextToken == TOK_LESSEQUAL;
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
        case TOK_INVALIDLIT:
            checkError110();

        default:                    
            printf("Unknown Token: |%s|\n", yytext);
            exit(EXIT_FAILURE); 
    }

    return nextToken;
}

void program(){

    //if(print_debug)output("PROGRAM");
    //lex();
    
    if(print_debug){psp(); printf("enter <program>\n");}
    level++;

    // initalize the symboltable
    symbolTable = createHashSet();

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
        classDecl();
    }
    else if(nextToken == TOK_FUN){
        if(print_debug)output("Function");
        funDecl();
    }
    else if(nextToken == TOK_VAR){
        if(print_debug)output("Variable");
        varDecl();
    }
    else if(startOfStatement()){
        if(print_debug)output("Statement");
        statement();
    }
    else{
        //need some sort of error msg here
        printf("Misshandeled declaration()\n");
        exit(EXIT_FAILURE);
    }

    level--;
    if(print_debug){psp(); printf("exit <Declaration>\n");}
}

void classDecl(){

    if(print_debug){psp(); printf("enter <classDecl>\n");}
    level++;

    if(print_debug)output("class");
    lex();

    if(print_debug)output("IDENTIFIER");
    insert(symbolTable, yytext);
    lex();

    if(nextToken == TOK_LESS){
        checkError203();
        if(print_debug)output("<");
        lex();
        checkError101();
        if(print_debug)output("IDENTIFIER");
        lex();
    }

    checkError201();
    if(print_debug)output("{");
    lex();

    while(nextToken == TOK_IDENT){
        function();
    }

    checkError201();
    if(print_debug)output("}");
    lex();

    level--;
    if(print_debug){psp(); printf("exit <classDecl>\n");}

}

void funDecl(){

    if(print_debug){psp(); printf("enter <funDecl>\n");}
    level++;

    if(print_debug)output("fun");
    lex();

    function();

    level--;
    if(print_debug){psp(); printf("exit <funDecl>\n");}

}

void function(){
    if(print_debug)output("IDENTIFIER");
    insert(symbolTable, yytext);
    lex();

    checkError202();
    if(print_debug)output("(");
    lex();

    if(nextToken == TOK_IDENT){
        if(print_debug)output("IDENTIFIER");
        lex();

        while(nextToken == TOK_COMMA){
            checkError205();
            if(print_debug)output(",");
            lex();
            if(print_debug)output("IDENTIFIER");
            lex();
        }
    }

    checkError202();
    if(print_debug)output(")");
    lex();

    if(print_debug)output("block");
    block();
}

void varDecl(){
    if(print_debug){psp(); printf("enter <varDecl>\n");}
    level++;

    if(print_debug)output("var");
    lex();

    if(print_debug)output("IDENTIFIER");
    checkError102();
    insert(symbolTable, yytext);
    lex();

    if(nextToken == TOK_ASSIGN){
        checkError203();
        if(print_debug)output("=");
        lex();
        
        if(print_debug)output("expression");
        expression();
    }

    checkError200();
    if(print_debug)output(";");
    lex();

    level--;
    if(print_debug){psp(); printf("exit <varDecl>\n");}

}

// start of statements
void statement(){

    if(print_debug){psp(); printf("enter <statement>\n");}
    level++;

    if(nextToken == TOK_FOR){
        // for statement
        if(print_debug)output("for stmt");
        forStmt();
    } 
    else if(nextToken == TOK_IF){
        // if statement
        if(print_debug)output("if stmt");
        ifStmt();
    }
    else if(nextToken == TOK_PRINT){
        // print statement
        if(print_debug)output("print smt");
        printStmt();
    }
    else if(nextToken == TOK_RETURN){
        // return statement
        if(print_debug)output("return stmt");
        returnStmt();
    }
    else if(nextToken == TOK_WHILE){
        // while statement
        if(print_debug)output("while stmt");
        whileStmt();
    }
    else if(nextToken == TOK_OPENBRACE){
        // block
        if(print_debug)output("block");
        block();
    }
    else{
        // expression
        if(print_debug)output("expression stmt");
        exprStmt();
    }

    level--;
    if(print_debug){psp(); printf("exit <statement>\n");}

}

void ifStmt(){
    
    if(print_debug){psp(); printf("enter <if_statement>\n");}
    level++;

    if(print_debug)output("if");
    lex();

    checkError202();
    if(print_debug)output("(");
    lex();

    if(print_debug)output("expression");
    expression();

    checkError202();
    if(print_debug)output(")");
    lex();

    if(print_debug)output("statement");
    statement();

    // optional else block
    if(nextToken == TOK_ELSE){
        if(print_debug)output("else");
        lex();

        if(print_debug)output("statement");
        statement();
    }

    level--;
    if(print_debug){psp(); printf("exit <if_statement>\n");}

}

void printStmt(){

    if(print_debug){psp(); printf("enter <print_statement>\n");}
    level++;

    if(print_debug)output("print");
    lex();

    if(print_debug)output("expression");
    expression();

    checkError200();
    if(print_debug)output(";");
    lex();

    level--;
    if(print_debug){psp(); printf("exit <print_statement>\n");}

}

void returnStmt(){

    if(print_debug){psp(); printf("enter <return_statement\n");}
    level++;

    if(print_debug)output("return");
    lex();

    if(startOfExpr()){
        if(print_debug)output("expression");
        expression();
    }

    checkError200();
    if(print_debug)output(";");
    lex();

    level--;
    if(print_debug){psp(); printf("exit <return_statement\n");}

}

void whileStmt(){

    if(print_debug){psp(); printf("enter <while_statement\n");}
    level++;

    if(print_debug)output("while");
    lex();

    checkError202();
    if(print_debug)output("(");
    lex();

    if(print_debug)output("expression");
    expression();

    checkError202();
    if(print_debug)output(")");
    lex();

    if(print_debug)output("statement");
    statement();

    level--;
    if(print_debug){psp(); printf("exit <while_statement\n");}

}

void block(){

    if(print_debug){psp(); printf("enter <block>\n");}
    level++;

    checkError201();
    if(print_debug)output("{");
    lex();

    while(startOfDec()){
        if(print_debug)output("declaration");
        declaration();
    }

    checkError201();
    if(print_debug)output("}");
    lex();

    level--;
    if(print_debug){psp(); printf("exit <block>\n");}

}

void exprStmt(){

    if(print_debug){psp(); printf("enter <expression_statement\n");}
    level++;

    if(print_debug)output("expression");
    expression();

    checkError200();
    if(print_debug)output(";");
    lex();

    level--;
    if(print_debug){psp(); printf("exit <expression_statement\n");}
}

void forStmt(){

    /*
        Disclaimer: 
        The function to parse a for loop is admitatley messy
        I followed the grammar rules for lox as notated in the Appendix
        (Section A1.1.2)
        https://craftinginterpreters.com/appendix-i.html
    */

    if(print_debug){psp(); printf("enter <for_statement>\n");}
    level++;

    if(print_debug)output("for");
    lex();

    checkError202();
    if(print_debug)output("(");
    lex();

    // select from 1 of 3 branches in 'for'
    if(nextToken == TOK_VAR){
        if(print_debug)output("var_dec");
        varDecl();
    }
    else if(startOfExpr()){
        if(print_debug)output("expr_stmt");
        exprStmt();
    }
    else if(nextToken == TOK_SEMICOLON){
        if(print_debug)output(";");
        lex();
    }
    else{
        //printf("Error in forStmt()\n");
        //exit(EXIT_FAILURE);
        checkError909();
    }

    // expression? 
    if(startOfExpr()){
        if(print_debug)output("expression");
        expression();

        checkError200();
        if(print_debug)output(";");
        lex();
    }

    // another optional expression
    if(startOfExpr()){
        if(print_debug)output("expression");
        expression();
    }

    checkError202();
    if(print_debug)output(")");
    lex();

    if(print_debug)output("statement");
    statement();

    level--;
    if(print_debug){psp(); printf("exit <for_statement>\n");}

}

void expression(){

    if(print_debug){psp(); printf("enter <expression>\n");}
    level++;

    if(print_debug)output("assignment");
    assignment();

    level--; 
    if(print_debug){psp(); printf("exit <expression>\n");}
}

void assignment(){

    if(print_debug){psp(); printf("enter <assignment>\n");}
    level++;

    if(print_debug)output("logic_or");
    logicOr();

    
    if(nextToken == TOK_ASSIGN){
        
        if(print_debug)output("=");
        lex();

        if(print_debug)output("assignment");
        assignment();
    }

    level--;
    if(print_debug){psp(); printf("exit <assignment>\n");}
}

void logicOr(){

    if(print_debug){psp(); printf("enter <logic_or>\n");}
    level++;

    if(print_debug)output("logic_and");
    logicAnd();

    // parse the rest of logics
    while(nextToken == TOK_OR){

        if(print_debug)output("or");
        lex();

        if(print_debug)output("logic_and");
        logicAnd();

    }

    level--;
    if(print_debug){psp(); printf("exit <logic_or>\n");}

}

void logicAnd(){

    if(print_debug){psp(); printf("enter <logic_and>\n");}
    level++;

    if(print_debug)output("equality");
    equality();

    // parse the rest of logics
    while(nextToken == TOK_AND){

        if(print_debug)output("and");
        lex();

        if(print_debug)output("equality");
        equality();

    }

    level--;
    if(print_debug){psp(); printf("exit <logic_and>\n");}

}

void equality(){

    if(print_debug){psp(); printf("enter <equality>\n");}
    level++;

    if(print_debug)output("comparison");
    comparison();

    while(nextToken == TOK_NOTEQUAL || nextToken == TOK_EQUAL){
        switch(nextToken){
            case TOK_NOTEQUAL:
                if(print_debug)output("!=");
                lex();
                break;
            case TOK_EQUAL:
                if(print_debug)output("==");
                lex();
                break;
        }

        if(print_debug)output("comparison");
        comparison();
    }

    level--;
    if(print_debug){psp(); printf("exit <equality>\n");}

}

void comparison(){

    if(print_debug){psp(); printf("enter <comparison>\n");}
    level++;

    if(print_debug)output("term");
    term();

    // parse the rest of the comparisons
    while(isCompareOp()){
        switch(nextToken){
            case TOK_LESS:
                if(print_debug)output("<");
                lex();
                break;
            case TOK_LESSEQUAL:
                if(print_debug)output("<=");
                lex();
                break;
            case TOK_GREATER:
                if(print_debug)output(">");
                lex();
                break;
            case TOK_GREATEQUAL:
                if(print_debug)output(">=");
                lex();
                break;
        }

        if(print_debug)output("term");
        term();
    }

    level--;
    if(print_debug){psp(); printf("exit <comparison>\n");}

}

void term(){

    if(print_debug){psp(); printf("enter <term>\n");}
    level++;

    if(print_debug)output("factor");
    factor();

    // parse however many unarys are left
    while(nextToken == TOK_MINUS || nextToken == TOK_PLUS){
        if(nextToken == TOK_MINUS){
            if(print_debug)output("-");
            lex();
        }
        else{
            if(print_debug)output("+");
            lex();
        }

        if(print_debug)output("factor");
        factor();
    }

    level--;
    if(print_debug){psp(); printf("exit <term>\n");}

}

void factor(){

    if(print_debug){psp(); printf("enter <factor>\n");}
    level++;

    if(print_debug)output("unary");
    unary();

    // parse however many unarys are left
    while(nextToken == TOK_DIV || nextToken == TOK_MULT){
        if(nextToken == TOK_DIV){
            if(print_debug)output("/");
            lex();
        }
        else{
            if(print_debug)output("*");
            lex();
        }

        if(print_debug)output("unary");
        unary();
    }

    level--;
    if(print_debug){psp(); printf("exit <factor>\n");}

}

void unary(){

    if(print_debug){psp(); printf("enter <unary>\n");}
    level++;

    // decide which type of unary we have
    if(startOfPrimary()){
        if(print_debug)output("call");
        call();
    }
    else if(nextToken == TOK_NOT){
        if(print_debug)output("!");
        lex();
        if(print_debug)output("unary");
        unary();
    }
    else if(nextToken == TOK_MINUS){
        if(print_debug)output("-");
        lex();
        if(print_debug)output("unary");
        unary();
    }
    else{
        checkError909();
    }

    level--;
    if(print_debug){psp(); printf("exit <unary>\n");}    

}

void call(){

    if(print_debug){psp(); printf("enter <call>\n");}
    level++;

    if(print_debug)output("primary");
    primary();

    // parse how ever many (args) or .ident there are
    // this looks like a mess but not sure of how else
    // to accomplish the parse
    while(nextToken == TOK_OPENPAREN || nextToken == TOK_DOT){

        // decide between which type of call
        if (nextToken == TOK_OPENPAREN)
        {
            if (print_debug)output("open-paren");
            lex();

            // arguments => expression (, expression)*
            if(startOfExpr()){
                if(print_debug)output("expression");
                expression();
            }
            // parse however many args
            while(nextToken == TOK_COMMA){
                if(print_debug)output(",");
                lex();
                if(print_debug)output("expression");
                expression();
            }

            checkError202();
            if(print_debug)output("close-paren");
            lex();
        }
        else
        {
            checkError203();
            if (print_debug)output(".");
            lex();
            //checkError100();
            if (print_debug)output("IDENTIFIER");
            lex();
        }
    }

    level--;
    if(print_debug){psp(); printf("exit <call>\n");}
}

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
            insert(symbolTable, yytext);
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
            checkError100();
            if(print_debug)output("IDENTIFIER");
            lex();
            break;

        case TOK_STRING:
            if(print_debug)output("STRING LIT");
            lex();
            break;

        default:
            checkError909();
            break;
    } 

    level--;
    if(print_debug){psp(); printf("exit <primary>\n");}
}



