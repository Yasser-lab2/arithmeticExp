#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

Stack operand;
Stack operator;

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

int calculate(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return 0;
}

int evaluate(char *exp)
{
    initialize(&operand);
    initialize(&operator);

    while (*exp != '\0')
    {
        if (isOperand(*exp))
        {
            int num = 0;
            do
            {
                num = num * 10 + (*exp - '0');
                exp++;
            } while (isOperand(*exp));

            push(&operand, num);
            continue;
        }
        else if (isOperator(*exp))
        {
            while (!isEmpty(&operator) && precedence(peek(&operator)) >= precedence(*exp))
            {
                int val2 = pop(&operand);
                int val1 = pop(&operand);
                char op = pop(&operator);
                push(&operand, calculate(val1, val2, op));
            }
            push(&operator, *exp);
        }
        exp++;
    }

    while (!isEmpty(&operator))
    {
        int val2 = pop(&operand);
        int val1 = pop(&operand);
        char op = pop(&operator);
        push(&operand, calculate(val1, val2, op));
    }

    return pop(&operand);
}

int main()
{
    printf("Hello, World! from bekhhh \n");
    int result = evaluate("13+5*2-8/4");
    printf("Result: %d\n", result);
    return 0;
}