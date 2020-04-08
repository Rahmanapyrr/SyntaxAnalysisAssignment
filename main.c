/* front.c - a lexical analyzer system for simple
 arithmetic expressions */

// Adding this EBNF statement to the code in the book: "<stmt> → id = <expr>"

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


char CHARS[] = "src.in";

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
void expr();
void error();
void stmt();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/******************************************************/
/* main driver */
main() {
/* Open the input data file and process its contents */
 if ((in_fp = fopen(CHARS, "r")) == NULL)
 printf("ERROR - cannot open front.in \n");
 else {
  getChar();
  
  //
  do {
   lex();
   stmt();
 } 
  while (nextToken != EOF);
 }
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses
 and return the token */
int lookup(char ch) {
 switch (ch) {
  case '(':
   addChar();
   nextToken = LEFT_PAREN;
   break;
   
 case ')':
   addChar();
   nextToken = RIGHT_PAREN;
   break;
   
 case '+':
  addChar();
  nextToken = ADD_OP;
  break;
   
 case '=':
  addChar();
  nextToken = ASSIGN_OP;
  break;
   
 case '-':
  addChar();
  nextToken = SUB_OP;
  break;
 
 case '*':
  addChar();
  nextToken = MULT_OP;
  break;
   
 case '/':
  addChar();
  nextToken = DIV_OP;
  break;
   
 default:
  addChar();
  nextToken = EOF;
  break;
 }
 
 return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar() {
 if (lexLen <= 98) {
 lexeme[lexLen++] = nextChar;
 lexeme[lexLen] = 0;
 }
 else
 printf("Error - lexeme is too long \n");
}

/*****************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar() {
 if ((nextChar = getc(in_fp)) != EOF) {
  if (isalpha(nextChar))
  charClass = LETTER;
 else if (isdigit(nextChar))
  charClass = DIGIT;
 else charClass = UNKNOWN;
 }
 else
  charClass = EOF;
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it
   returns a non-whitespace character */
void getNonBlank() {
 while (isspace(nextChar))
  getChar();
}
/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex() {
 lexLen = 0;
 getNonBlank();
 switch (charClass) {
   /* Parse identifiers */
 case LETTER:
  addChar();
  getChar();
  while (charClass == LETTER || charClass == DIGIT) {
     addChar();
     getChar();
 }
 nextToken = IDENT;
 break;
   
 /* Parse integer literals */
 case DIGIT:
   addChar();
   getChar();
   while (charClass == DIGIT) {
    addChar();
    getChar();
 }
 nextToken = INT_LIT;
 break;
/* Parentheses and operators */
 case UNKNOWN:
  lookup(nextChar);
  getChar();
 break;
/* EOF */
 case EOF:
 nextToken = EOF;
 lexeme[0] = 'E';
 lexeme[1] = 'O';
 lexeme[2] = 'F';
 lexeme[3] = 0;
 break;
 } /* End of switch */
 
 printf("Next token is: %d, Next lexeme is %s\n",
 nextToken, lexeme);
 return nextToken;
} /* End of function lex */

void error(){
  printf("An error occured at %d\n", nextToken);
} /* End of function error */

void  term() {  
  printf("Enter <term>\n");  
  factor(); 
 while (nextToken == MULT_OP || nextToken == DIV_OP) {    
    lex();    
    factor();  
  }  
  printf("Exit <term>\n"); 

}  /* End of function term */


/* expr   Parses strings in the language generated by the rule:   <expr> -> <term> {(+ | -) <term>}   */ 
void  expr() {
  printf("Enter <expr>\n");
  term();
 
 while  (nextToken == ADD_OP || nextToken == SUB_OP) {    
    lex();    
    term();  
  }  
  
  printf("Exit <expr>\n"); 

}  /* End of function expr */

void stmt(){
  if(nextToken == IDENT){
    lex();
   else if(nextToken == ASSIGN_OP){
      expr();
    }
  }
} /* End of stmt function */

void factor() {  
  printf("Enter <factor>\n");
  if (nextToken == IDENT || nextToken == INT_LIT){
    lex();
  }  
  else {    
    if (nextToken == LEFT_PAREN) {      
      lex();    
      expr();
      if (nextToken == RIGHT_PAREN)
        lex();
      else        
        error();    
    }  
     else      
      error();
  } 
  printf("Exit <factor>\n"); }  /* End of factor function */
