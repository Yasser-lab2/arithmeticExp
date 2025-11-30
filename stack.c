#include "stack.h"
#include <stdio.h>

// Initialise la pile en mettant l'indice top à -1
void initialize(Stack *s) {
    s->top = -1;
}

// Vérifie si la pile est vide
bool isEmpty(Stack *s) {
    // Cast explicite vers bool
    return (bool)(s->top == -1);
}

// Vérifie si la pile est pleine
bool isFull(Stack *s) {
    // Cast explicite vers bool
    return (bool)(s->top == MAX_SIZE - 1);
}

// Ajoute un élément au sommet de la pile
void push(Stack *s, Node *value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

// Retire et retourne l'élément au sommet de la pile
Node *pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        // Cast explicite du pointeur NULL
        return (Node *)NULL;     
    }
    // Cast explicite du pointeur retourné
    return (Node *)s->items[(s->top)--];
}

// Retourne l'élément au sommet sans le retirer
Node *peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        // Cast explicite du pointeur NULL
        return (Node *)NULL;     
    }
    // Cast explicite du pointeur retourné
    return (Node *)s->items[s->top];
}