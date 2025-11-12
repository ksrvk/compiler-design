#include <stdio.h>
#include <ctype.h>

enum TokenType {
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    SPECIAL,
    END_OF_FILE,
    UNKNOWN
};

void printToken(enum TokenType type, char *lexeme) {
    switch(type) {
        case IDENTIFIER:
            printf("Identifier: %s\n", lexeme);
            break;
        case NUMBER:
            printf("Number: %s\n", lexeme);
            break;
        case OPERATOR:
            printf("Operator: %s\n", lexeme);
            break;
        case SPECIAL:
            printf("Special symbol: %s\n", lexeme);
            break;
        case END_OF_FILE:
            printf("End of file reached\n");
            break;
        default:
            printf("Unknown token: %s\n", lexeme);
    }
}

int main() {
    char c;
    char lexeme[100];
    int lexLen;

    printf("Enter input (Ctrl+D to end):\n");

    while ((c = getchar()) != EOF) {
        // Skip whitespace
        if (isspace(c)) continue;

        lexLen = 0;

        // If letter: identifier
        if (isalpha(c)) {
            lexeme[lexLen++] = c;
            while ((c = getchar()) != EOF && (isalnum(c))) {
                lexeme[lexLen++] = c;
            }
            lexeme[lexLen] = '\0';
            printToken(IDENTIFIER, lexeme);
            if (c == EOF) break;
            ungetc(c, stdin);
        }
        // If digit: number
        else if (isdigit(c)) {
            lexeme[lexLen++] = c;
            while ((c = getchar()) != EOF && isdigit(c)) {
                lexeme[lexLen++] = c;
            }
            lexeme[lexLen] = '\0';
            printToken(NUMBER, lexeme);
            if (c == EOF) break;
            ungetc(c, stdin);
        }
        // If operator (+, -, *, /)
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            lexeme[lexLen++] = c;
            lexeme[lexLen] = '\0';
            printToken(OPERATOR, lexeme);
        }
        // Special symbols (parentheses, comma, semicolon etc.)
        else if (c == '(' || c == ')' || c == ',' || c == ';' || c == '{' || c == '}') {
            lexeme[lexLen++] = c;
            lexeme[lexLen] = '\0';
            printToken(SPECIAL, lexeme);
        }
        else {
            lexeme[lexLen++] = c;
            lexeme[lexLen] = '\0';
            printToken(UNKNOWN, lexeme);
        }
    }

    printToken(END_OF_FILE, "");

    return 0;
}
