%{
int words = 0;
int lines = 0;
%}

%%
\n        { lines++; }
[a-zA-Z0-9]+  { words++; }
.          { /* ignore other characters */ }
%%

int main(int argc, char *argv[]) {
    yylex();
    printf("Number of words: %d\n", words);
    printf("Number of lines: %d\n", lines);
    return 0;
}
