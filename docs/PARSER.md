--Lox Grammer Rules in EBNF--

<program>       =   <declaration>* EOF
<declaration>   =   (<classDec> | <funDec> | <varDec> | <statement>)
<classDec>      =   class IDENTIFIER  ( < IDENTIFIER) { <funDec>* }
<funDec>        =   fun <statement> ;
<varDec>        =   var IDENTIFIER ( = <expression>) ;



expression     = assignment ;

assignment     = ( call "." )? IDENTIFIER "=" assignment
               | logic_or ;

logic_or       = logic_and ( "or" logic_and )* ;
logic_and      = equality ( "and" equality )* ;
equality       = comparison ( ( "!=" | "==" ) comparison )* ;
comparison     = term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           = factor ( ( "-" | "+" ) factor )* ;
factor         = unary ( ( "/" | "*" ) unary )* ;
unary          = ( "!" | "-" ) unary | call ;
call           = primary ( "(" arguments? ")" | "." IDENTIFIER )* ;
primary        = "true" | "false" | "nil" | "this"
               | NUMBER | STRING | IDENTIFIER
               | "(" expression ")"
               | "super" "." IDENTIFIER ;

arguments      = expression ( "," expression )* ;

assignemnt     = call "=" assignment | logic_or 

