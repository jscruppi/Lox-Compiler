--Lox Grammer Rules in EBNF--

<program>       =   <declaration>* EOF
<declaration>   =   (<classDec> | <funDec> | <varDec> | <statement>)
<classDec>      =   class IDENTIFIER  ( < IDENTIFIER) { <funDec>* }
<funDec>        =   fun <statement> ;
<varDec>        =   var IDENTIFIER ( = expression) ;


