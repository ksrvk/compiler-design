//yacc
%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token ID
%left '+'
%left '*'

%%
E: T EPrime { $$ = $1 + $2; }
 ;

EPrime:
      '+' T EPrime { $$ = $2 + $3; }
    | /* epsilon */ { $$ = 0; }
 ;

T: F TPrime { $$ = $1 * $2; }
 ;

TPrime:
      '*' F TPrime { $$ = $2 * $3; }
    | /* epsilon */ { $$ = 1; }
 ;

F: '(' E ')' { $$ = $2; }
 | ID       { $$ = $1; }
 ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter expression:\n");
    if (yyparse() == 0) {
        printf("Parsing completed successfully.\n");
    }
    return 0;
}




//lex


%{
#include "y.tab.h"
%}

%%
[0-9]+    { yylval = atoi(yytext); return ID; }
[ \t\n]+  { /* skip whitespace */ }
'+'       { return '+'; }
'*'       { return '*'; }
'('       { return '('; }
')'       { return ')'; }
.         { printf("Invalid character %s\n", yytext); }
%%

int yywrap() {
    return 1;
}


//lex lexfile.l
//yacc -d yaccfile.y
//gcc lex.yy.c y.tab.c -o calc -ll
//./calc

