/*

    Header files for all the nodes used for the parser

*/


#ifndef NODES_H
#define NODES_H

typedef enum{
    PROGRAM,
    DECLARATION,
    CLASSDECL,
    FUNDECL,
    VARDECL,
    STATEMENT,
    EXPRSTMT,
    FORSTMT,
    IFSTMT,
    PRINTSTMT,
    RETURNSTMT,
    WHILESTMT,
    BLOCK,
    EXPRESSION,
    ASSIGNMENT,
    LOGIC_OR,
    LOGIC_AND,
    EQUALITY,
    COMPARISON,
    TERM,
    FACTOR,
    UNARY,
    CALL,
    PRIMARY
} type;

typedef struct{
    type node_type;
    int level;
    void *next; // ASTNode -> should find a better way to make that more readable
} ASTNode;

typedef struct{
    ASTNode base;
    enum{
        TRUE,
        FALSE,
        NIL,
        THIS,
        NUMBER,
        STRING,
        IDENT,
        NEXTEXPR,
        SUPERCALL
    } tag;
    union{
        char *keyword;
        char *ident;
        char *string;
        float number;
        //  TODO - Add expression node here
        // *ident will be used to also store the 'super.ident' primary rule
    } data;
} PrimaryNode;

#endif
