# LOX-Compiler 

Goal is to write a compiler for the LOX Language, a language originally written to help programars learn how interpreturs work. Details for this can be found at:
https://craftinginterpreters.com/the-lox-language.html#top

## Development

As of writing, I currently have a tokenizer that can tokenize up to 47 different tokens. This was achienved through the open-source tool flex OwO

I am currently working on implementing the parser now. As of writing, the parser can parse LOX files, and contains a handful of error checks (at compile time) to check for syntax errors. The next step is to have the parser generate an AST (abstract syntax tree).

All of this is planned to be implemented in C (because to heck with C++)