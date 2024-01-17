#ifndef PILE
#define PILE
typedef struct Stack {
    char top;
    struct Stack *next;
} Stack;

/* Stack constructeur */
Stack * init_stack();

/* Stack destructeur */
bool delete_stack(Stack **);

/* Ajoute un élement au dessus de la pile */
void push(Stack **, char);

/* Supprime l'élément du haut la pile et renvoie sa valeur */
/* s'il existe */
char pop(Stack **);

/* Affiche l'élément du haut de la pile s'il exite */
char peek(Stack *);

/* Renvoie true si la pile est vide, false sinon */
bool is_empty(Stack *);

/* Affiche l'état de la pile */
void print_stack(Stack *);
#endif
