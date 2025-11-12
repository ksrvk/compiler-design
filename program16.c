#include <stdio.h>
#define STACK_SIZE 100

typedef struct { int id, vars[10]; } Frame;
Frame stack[STACK_SIZE];
int top = -1;

void push(int id) {
    if (top == STACK_SIZE - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    stack[++top].id = id;
    printf("Function %d called. Frame at %d.\n", id, top);
}

void pop() {
    if (top < 0) {
        printf("Stack Underflow!\n");
        return;
    }
    printf("Function %d returned. Frame %d removed.\n", stack[top--].id, top + 1);
}

void show() {
    printf("\nCurrent Stack:\n");
    if (top < 0) {
        printf("  [Empty Stack]\n");
        return;
    }
    for (int i = top; i >= 0; i--)
        printf("  Frame %d: Function ID %d\n", i, stack[i].id);
}

int main() {
    int ch, id;
    while (1) {
        printf("\n1.Push  2.Pop  3.Display  4.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter function ID: ");
                scanf("%d", &id);
                push(id);
                break;
            case 2: pop(); break;
            case 3: show(); break;
            case 4: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
