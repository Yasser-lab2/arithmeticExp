#ifndef STACK_H
#define STACK_H
#include "node.h"

#include <stdbool.h>

#define MAX_SIZE 100

typedef struct
{
    Node *items[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *s);
bool isEmpty(Stack *s);
bool isFull(Stack *s);
void push(Stack *s, Node *value);
Node *pop(Stack *s);
Node *peek(Stack *s);

#endif 