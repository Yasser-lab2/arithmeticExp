#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
    bool isOperator;
    char op;
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *createOperandNode(int value);
Node *createOperatorNode(char op);
int evaluateTree(const Node *root);
void freeTree(Node *root);


#endif