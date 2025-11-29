#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "stack.h"

int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int isOperand(char c)
{
    return (c >= '0' && c <= '9');
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

 void applyOperator(Stack *operands, Stack *operators)
{
    Node *right = pop(operands);
    Node *left = pop(operands);
    Node *opNode = pop(operators);

    if (!right || !left || !opNode)
    {
        fprintf(stderr, "Invalid expression\n");
        exit(EXIT_FAILURE);
    }

    opNode->left = left;
    opNode->right = right;
    push(operands, opNode);
}

int evaluate(const char *exp)
{
    Stack operand;
    Stack operator;
    initialize(&operand);
    initialize(&operator);

    while (*exp != '\0')
    {
        if (*exp == ' ')
        {
            exp++;
            continue;
        }

        if (isOperand(*exp))
        {
            int num = 0;
            do
            {
                num = num * 10 + (*exp - '0');
                exp++;
            } while (isOperand(*exp));

            push(&operand, createOperandNode(num));
            continue;// to avoid extra increment at the end
        }
        else if (isOperator(*exp))
        {
            Node *currentOp = createOperatorNode(*exp);
            while (!isEmpty(&operator) && precedence(peek(&operator)->op) >= precedence(currentOp->op))
            {
                applyOperator(&operand, &operator);
            }
            push(&operator, currentOp);
        }
        exp++;
    }

    while (!isEmpty(&operator))
    {
        applyOperator(&operand, &operator);
    }

    Node *root = pop(&operand);
    if (!root)
    {
        fprintf(stderr, "Invalid expression\n");
        exit(EXIT_FAILURE);
    }

    int result = evaluateTree(root);
    freeTree(root);
    return result;
}

int main()
{
    printf("Hello, World! from bekhhh \n");
    int result = evaluate("3 + 5 * 2 - 8 / 4");
    printf("Result: %d\n", result);
    return 0;
}
