#ifndef STACK_H
#define STACK_H
#include "node.h"

#include <stdbool.h>

#define MAX_SIZE 100

// Structure de la pile contenant des pointeurs vers des Noeuds
typedef struct
{
    Node *items[MAX_SIZE]; // Tableau de pointeurs de noeuds
    int top;               // Indice du sommet de la pile
} Stack;

// Prototypes des opérations de pile
void initialize(Stack *s);
bool isEmpty(Stack *s);
bool isFull(Stack *s);
void push(Stack *s, Node *value);
Node *pop(Stack *s);
Node *peek(Stack *s);

#endif