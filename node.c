#include "node.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

// Crée un noeud feuille contenant une valeur numérique (opérande)
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
    // Retourne le pointeur vers le nouveau noeud avec un cast explicite
    return (Node *)n;
}

// Crée un noeud interne contenant un opérateur
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
    // Retourne le pointeur vers le nouveau noeud avec un cast explicite
    return (Node *)n;
}

// Fonction auxiliaire pour effectuer le calcul arithmétique de base
int evaluateOperator(int left, int right, char op)
{
    switch (op)
    {
    case '+':
        return (int)(left + right);
    case '-':
        return (int)(left - right);
    case '*':
        return (int)(left * right);
    case '/':
        // Note: La division par zéro n'est pas gérée explicitement ici, 
        // cela pourrait causer un crash si right est 0.
        return (int)(left / right);
    default:
        fprintf(stderr, "Unknown operator: %c\n", op);
        exit(EXIT_FAILURE);
    }
}

// Évalue la valeur de l'arbre d'expression de manière récursive
int evaluateTree(const Node *root)
{
    if (!root)
    {
        fprintf(stderr, "Cannot evaluate an empty tree\n");
        exit(EXIT_FAILURE);
    }

    // Si c'est une feuille (nombre), on retourne sa valeur
    if (!root->isOperator)
    {
        return (int)(root->value);
    }

    // Sinon, on évalue récursivement les sous-arbres gauche et droit
    int leftValue = evaluateTree(root->left);
    int rightValue = evaluateTree(root->right);
    
    // On applique l'opérateur et on retourne le résultat entier
    return (int)evaluateOperator(leftValue, rightValue, root->op);
}

// Libère la mémoire allouée pour l'arbre (parcours post-ordre)
void freeTree(Node *root)
{
    if (!root)
    {
        return; // Fonction void, pas de valeur à caster
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}