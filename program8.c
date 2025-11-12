#include <stdio.h>
#include <ctype.h>

#define MAX 100

char input[MAX];
int i = 0;
char lookahead;

void E();
void EPrime();
void T();
void TPrime();
void F();

void match(char t) {
    if (lookahead == t) {
        lookahead = input[++i];
    } else {
        printf("Error: Expected %c but found %c\n", t, lookahead);
        exit(1);
    }
}

void E() {
    T();
    EPrime();
}

void EPrime() {
    if (lookahead == '+') {
        match('+');
        T();
        EPrime();
    }
}

void T() {
    F();
    TPrime();
}

void TPrime() {
    if (lookahead == '*') {
        match('*');
        F();
        TPrime();
    }
}

void F() {
    if (lookahead == '(') {
        match('(');
        E();
        match(')');
    } else if (isalnum(lookahead)) {
        match(lookahead); // match id which is a single letter or digit
    } else {
        printf("Error: Unexpected symbol %c\n", lookahead);
        exit(1);
    }
}

int main() {
    printf("Enter input string (no spaces): ");
    scanf("%s", input);
    lookahead = input[i];
    E();
    if (lookahead == '\0') {
        printf("Parsing successful\n");
    } else {
        printf("Parsing error at %c\n", lookahead);
    }
    return 0;
}
