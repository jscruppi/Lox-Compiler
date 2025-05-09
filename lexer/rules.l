/*
    All the rules associated with the Lox Lexer and its tokens

    Author: Joe Scruppi

*/

%option yylineno
%option noyywrap
%{
    #include "lexer.h"
    int line_number = 1;

%}

%%

\/\/.* 

"class"         {return TOK_CLASS;}
"else"         {return TOK_ELSE;}
"false"         {return TOK_FALSE;}
"for"           {return TOK_FOR;}
"fun"           {return TOK_FUN;}
"if"            {return TOK_IF;}
"nil"           {return TOK_NIL;}
"or"            {return TOK_OR;}
"print"         {return TOK_PRINT;}
"return"        {return TOK_RETURN;}
"super"         {return TOK_SUPER;}
"this"          {return TOK_THIS;}
"true"          {return TOK_TRUE;}
"var"           {return TOK_VAR;}
"while"         {return TOK_WHILE;}

\(              {return TOK_OPENPAREN;}
\)              {return TOK_CLOSEPAREN;}
\{              {return TOK_OPENBRACE;}
\}              {return TOK_CLOSEBRACE;}
;               {return TOK_SEMICOLON;}
,               {return TOK_COMMA;}
\.              {return TOK_DOT;}
\[              {return TOK_OPENBRACK;}
\]              {return TOK_CLOSEBRACK;}
:               {return TOK_COLON;}

\+              {return TOK_PLUS;}
\-              {return TOK_MINUS;}
\*              {return TOK_MULT;}
\/              {return TOK_DIV;}
==              {return TOK_EQUAL;}
=               {return TOK_ASSIGN;}
!=              {return TOK_NOTEQUAL;}
\<=             {return TOK_LESSEQUAL;}
\>=             {return TOK_GREATEQUAL;}
!               {return TOK_NOT;}
\<              {return TOK_LESS;}
\>              {return TOK_GREATER;}
\&\&            {return TOK_AND;}
\|\|            {return TOK_OR;}

[0-9]+              {return TOK_INT;}
[0-9]+\.[0-9]+      {return TOK_FLOAT;}
\"[^\n]{0,80}\"     {return TOK_STRING;}
\"{81,}\"      {return TOK_INVALIDLIT;}
[A-Za-z_][A-Za-z0-9_]{0,32} {return TOK_IDENT;}
[A-Za-z_][A-Za-z0-9_]{33,}  {return TOK_INVALIDLIT;}
 
[ \t\r]+

[\n]        {line_number++;}

<<EOF>>     { return TOK_EOF; }

.           { return TOK_UNKNOWN; }

%%

