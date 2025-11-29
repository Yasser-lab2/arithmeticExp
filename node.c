#include "node.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

Node *createOperandNode(int value)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n)
    {
        perror("Failed to allocate operand node");
        exit(EXIT_FAILURE);
    }
    n->isOperator = false;
    n->op = '\0';
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node *createOperatorNode(char op)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n)
    {
        perror("Failed to allocate operator node");
        exit(EXIT_FAILURE);
    }
    n->isOperator = true;
    n->op = op;
    n->value = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
}

int evaluateOperator(int left, int right, char op)
{
    switch (op)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        return left / right;
    default:
        fprintf(stderr, "Unknown operator: %c\n", op);
        exit(EXIT_FAILURE);
    }
}

int evaluateTree(const Node *root)
{
    if (!root)
    {
        fprintf(stderr, "Cannot evaluate an empty tree\n");
        exit(EXIT_FAILURE);
    }

    if (!root->isOperator)
    {
        return root->value;
    }

    int leftValue = evaluateTree(root->left);
    int rightValue = evaluateTree(root->right);
    return evaluateOperator(leftValue, rightValue, root->op);
}

void freeTree(Node *root)
{
    if (!root)
    {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
