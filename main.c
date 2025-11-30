#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "stack.h"

// Vérifie si le caractère est un opérateur supporté
int isOperator(char c)
{
    // Cast explicite vers int (1 ou 0)
    return (int)(c == '+' || c == '-' || c == '*' || c == '/');
}

// Vérifie si le caractère est un chiffre
int isOperand(char c)
{
    // Cast explicite vers int
    return (int)(c >= '0' && c <= '9');
}

// Détermine la priorité des opérateurs pour l'ordre des opérations
int precedence(char op)
{
    if (op == '+' || op == '-')
        return (int)1;
    if (op == '*' || op == '/')
        return (int)2;
    return (int)0;
}

// Fonction utilitaire pour combiner deux opérandes et un opérateur en un sous-arbre
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

    // Le noeud opérateur devient le père des deux opérandes
    opNode->left = left;
    opNode->right = right;
    
    // On remet le sous-arbre complet sur la pile des opérandes
    push(operands, opNode);
}

// Fonction principale d'évaluation de l'expression en chaîne de caractères
int evaluate(const char *exp)
{
    Stack operand;  // Pile pour stocker les nombres (et sous-arbres)
    Stack operator; // Pile pour stocker les opérateurs
    initialize(&operand);
    initialize(&operator);

    while (*exp != '\0')
    {
        // Ignorer les espaces
        if (*exp == ' ')
        {
            exp++;
            continue;
        }

        // Si c'est un nombre, on le parse entièrement
        if (isOperand(*exp))
        {
            int num = 0;
            do
            {
                num = num * 10 + (*exp - '0');
                exp++;
            } while (isOperand(*exp));

            push(&operand, createOperandNode(num));
            continue; // pour éviter l'incrémentation supplémentaire à la fin de la boucle
        }
        // Si c'est un opérateur
        else if (isOperator(*exp))
        {
            Node *currentOp = createOperatorNode(*exp);
            // On traite les opérateurs de la pile qui ont une priorité supérieure ou égale
            while (!isEmpty(&operator) && precedence(peek(&operator)->op) >= precedence(currentOp->op))
            {
                applyOperator(&operand, &operator);
            }
            push(&operator, currentOp);
        }
        exp++;
    }

    // Traiter les opérateurs restants dans la pile
    while (!isEmpty(&operator))
    {
        applyOperator(&operand, &operator);
    }

    // La racine de l'arbre final est le seul élément restant dans la pile opérande
    Node *root = pop(&operand);
    if (!root)
    {
        fprintf(stderr, "Invalid expression\n");
        exit(EXIT_FAILURE);
    }

    // Évaluer l'arbre et libérer la mémoire
    int result = evaluateTree(root);
    freeTree(root);
    
    // Cast explicite du résultat final
    return (int)result;
}

int main()
{
    printf("Hello, World! from bekhhh \n");
    // Exemple d'évaluation : 3 + (5*2) - (8/4) = 3 + 10 - 2 = 11
    int result = evaluate("3 + 5 * 2 - 8 / 4");
    printf("Result: %d\n", result);
    
    // Cast explicite du code de retour du programme
    return (int)0;
}