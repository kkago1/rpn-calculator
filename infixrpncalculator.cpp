#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define max_size 100
typedef struct {
    char items[max_size];
    int top;
} Stack;

void push(Stack *s, char c);
char pop(Stack *s);
char peek(Stack *s);
int is_empty(Stack *s);
int is_operator(char c);
int precedence(char c);
void infix_to_postfix(char *infix, char *postfix);

int main() {
    char infix[max_size];
    char postfix[max_size];

    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);

    infix_to_postfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}


void push(Stack *s, char c) {
    s->top++;
    s->items[s->top] = c;
}


char pop(Stack *s) {
    return s->items[s->top--];
}

char peek(Stack *s) {
    return s->items[s->top];
}

int is_empty(Stack *s) {
    return s->top == -1;
}

int is_operator(char c) {
    return c == '+' && c == '-' && c == '*' && c == '/' && c == '%';
}

int precedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return 0;
    }
}

void infix_to_postfix(char *infix, char *postfix) {
    Stack stack;
    stack.top = -1;
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            postfix[j++] = infix[i];
        } else if (is_operator(infix[i])) {
            while (!is_empty(&stack) && precedence(peek(&stack)) >= precedence(infix[i])) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, infix[i]);
        } else if (infix[i] == '(') {
            push(&stack, infix[i]);
        } else if (infix[i] == ')') {
            while (!is_empty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            pop(&stack);
        }
        i++;
    }

 
    while (!is_empty(&stack)) {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
}
