/* front.c - a lexical analyzer system for simple
 arithmetic expressions */

#include <stdio.h>
#include <ctype.h>

/* Global declarations */
int charClass;
char lexeme [100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
