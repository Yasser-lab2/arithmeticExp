#include "stack.h"
#include <stdio.h>

void initialize(Stack *s) {
    s->top = -1;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

bool isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, Node *value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

Node *pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return NULL;     }
    return s->items[(s->top)--];
}

Node *peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return NULL;     }
    return s->items[s->top];
}
