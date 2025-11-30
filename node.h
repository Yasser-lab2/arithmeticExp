#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdlib.h>

// Structure représentant un noeud dans l'arbre d'expression
typedef struct Node
{
    bool isOperator;    // Vrai si le noeud contient un opérateur (+, -, *, /)
    char op;            // Le caractère de l'opérateur (si isOperator est vrai)
    int value;          // La valeur numérique (si isOperator est faux)
    struct Node *left;  // Pointeur vers le fils gauche
    struct Node *right; // Pointeur vers le fils droit
} Node;

// Prototypes des fonctions pour manipuler les noeuds
Node *createOperandNode(int value);
Node *createOperatorNode(char op);
int evaluateTree(const Node *root);
void freeTree(Node *root);

#endif