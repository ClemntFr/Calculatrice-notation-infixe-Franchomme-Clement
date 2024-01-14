#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pile.h"

/* Stack constructeur */
Stack * init_stack() {
    Stack *stack = (Stack *) malloc(sizeof(*stack));
    stack->top = '0';
    stack->next = NULL;
    return stack;
}

/* Stack destructeur */
bool delete_stack(Stack **stack) {
    Stack *buff = *stack;
    // Tant qu'on est pas arrivé au dernier élément
    // on free l'élément actuel
    while (buff != NULL) {
        buff = (*stack)->next;
        if (*stack != NULL)
            free(*stack);
        else
            // On ne devrait jamais passer ici
            return false;

        *stack = buff;
    }
    return true;
}

/* ajoute un élement au dessus de la pile */
void push(Stack **stack, char val) {
    /*
        On crée un nouvel élément puis on le définit comme la nouvelle adresse
        de la pile
    */
    Stack *new_stack = (Stack *) malloc(sizeof(*new_stack));
    new_stack->top = val;
    new_stack->next = *stack;
    *stack = new_stack;
}

/* Supprime un élément de la pile et renvoie sa valeur */
/* s'il existe */
char pop(Stack **stack) {
    Stack *buff = *stack;
    char tmp = (*stack)->top;
    if ((*stack)->next == NULL) {
        printf("Stack Underflow !\n");
        exit(EXIT_FAILURE);
        return '0';
    }
    buff = buff->next;
    free(*stack);
    *stack = buff;
    return tmp;
}

/* Affiche l'élément du haut de la pile s'il existe */
char peek(Stack *stack) {
    if (stack->next == NULL) {
        printf("Stack Underflow !\n");
        exit(EXIT_FAILURE);
        return '0';
    }
    return stack->top;
}

/* Renvoie true si la pile est vide, false sinon */
bool is_empty(Stack *stack) {
    return (stack->next == NULL);
}

/* Affiche tout ce qui est dans la pile séparé par des */
/* espace jusqu'a ce que le dernier élément soit attein */
void empty_stack(Stack **stack) {
    while ((*stack)->next != NULL) {
        printf("%c ", pop(stack));
    }
}

/* Affiche l'état de la pile */
void print_stack(Stack *stack) {
    Stack *tmp = stack;
    printf("Stack state : top -> | ");
    while (tmp->next != NULL) {
        printf("%c | ", tmp->top);
        tmp = tmp->next;
    }
    printf("\n");
}

/*
int main(void) {
    // Tests pour la pile
    Stack *stack = init_stack();
    push(&stack, 'a');
    push(&stack, 'b');
    print_stack(stack);
    printf("popped : %c\n", pop(&stack));
    push(&stack, 'c');
    print_stack(stack);
    empty_stack(&stack);
    printf("\n");
    print_stack(stack);
    empty_stack(&stack);
    
    if (!delete_stack(&stack)) {
        printf("An error occured while freeing the stack\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
*/
