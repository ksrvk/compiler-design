%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);

%}

%token DIGIT

%left '+'
%left '*'

%%
E: E '+' T    { $$ = $1 + $3; }
 | T          { $$ = $1; }
 ;

T: T '*' F    { $$ = $1 * $3; }
 | F          { $$ = $1; }
 ;

F: '(' E ')'  { $$ = $2; }
 | DIGIT      { $$ = $1; }
 ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter expression:\n");
    if (yyparse() == 0) {
        printf("Expression evaluated successfully.\n");
    }
    return 0;
}


//lex

%{
#include "y.tab.h"
%}

%%

[0-9]    { yylval = atoi(yytext); return DIGIT; }
[ \t]    { /* ignore whitespace */ }
[\n]     { return 0; }
[\+]     { return '+'; }
[\*]     { return '*'; }
[\(]     { return '('; }
[\)]     { return ')'; }
.        { printf("Invalid character: %s\n", yytext); }

%%

// lex lexfile.l
// yacc -d yaccfile.y
// gcc lex.yy.c y.tab.c -o calc
// ./calc

