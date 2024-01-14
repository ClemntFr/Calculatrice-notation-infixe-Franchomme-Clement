#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pile.h"

bool is_in(char a, char *tab) {
    /* 
        Renvoie true si un caractère est 
        dans une chaine de caractères,
        false sinon
    */
    int i = 0;
    while(tab[i] != '\0') {
        if (tab[i] == a)
            return true;
        i += 1;
    }
    
    return false;
}

bool is_operator(char op) {
    /*
        Renvoie true si le caractère d'entrée
        est un opérateur connu, false sinon
    */
    char operators[] = "+-*/^es()";
    return is_in(op, operators); 
}

bool is_operand(char op) {
    /*
        Renvoie true si le caractère d'entrée
        est une opérande connue
    */
    char operands[] = ".0123456789";
    return is_in(op, operands);
}

void print_operator(char op) {
    /*
        Affiche chaque opérateur 
        de manière a pouvoir l'évaluer
    */
    if (op == 'e')
        printf("exp ");
    else if (op == 's')
        printf("sqrt ");
    else
        printf("%c ", op);
}


int get_prio(char op) {
    /*
        Renvoie la priorité de chaque
        opérateur, -1 pour (
    */
    if (op == '+' || op == '-')
        return 0;
    else if (op == '*' || op == '/')
        return 1;
    else if (op == '^')
        return 2;
    else if (op == 'e' || op == 's')
        return 3;
    else
        return -1;
}

void check_prio(Stack **stack, char op) {
    /*
        Ajoute l'opérateur a la pile
        si celle ci est vide ou si la
        priorité de l'opérateur est 
        strictement supérieure a celle
        du premier élément de la pile
        Sinon pop le premier élément
        et recommence la vérification
    */
    if (is_empty(*stack)) {
        push(stack, op);
        return ;
    }
    int prio_op = get_prio(op);
    int prio_stack = get_prio(peek(*stack));

    if (prio_op > prio_stack) {
        push(stack, op);
    } else {
        print_operator(pop(stack));
        check_prio(stack, op);
    } 
}

void check_operator(Stack **stack, char op) {
    /*
        Ajoute l'opérateur a la pile si
        c'est une parenthèse ouvrante.
        Si c'est une parenthèse fermante,
        dépile jusqu'a en trouver une 
        ouvrante.
        Sinon vérifie la priorité de 
        l'opérateur.
    */
    if (is_operator(op)) {
        switch (op)
        {
        case '(':
            push(stack, '(');
            break;
        
        case ')':
            char top = pop(stack);
            while (top != '(') {
                print_operator(top);
                top = pop(stack);
            }
            break;
        
        default:
            check_prio(stack, op);
            break;
        }
    }
}

void convert(char *expr) {
    /*
        Prend en entrée une chaine de caractère
        contenant une expression en notation
        infixe et affiche cette dernière en
        notation postfixe

        Précondition : expr est une expression
        valide en notation infixe
    */
    Stack *stack = init_stack();
    int i = 0;
    // Tant qu'on arrive pas a la fin
    while (expr[i] != '\0') {
        if (is_operand(expr[i])) {
            // Tant qu'on a une opérande on l'affiche
            while(is_operand(expr[i]))
                printf("%c", expr[i++]);
            
            // On passe a l'affichage de l'opérande ou
            // opérateur suivant
            printf(" ");
        }
        // On vérifie si on a un opérateur, si oui on
        // gère l'état de la pile en conséquence
        check_operator(&stack, expr[i]);
        i += 1;
    }

    // On affiche tous les opérateurs restant dans la pile
    empty_stack(&stack);
    printf("\n");

    // On libère la mémoire prise par la pile
    delete_stack(&stack);
}

void convert_2() {
    /*
        Convertit une expression en notation infixe
        entrée sur l'entrée standard en notation 
        postfixe en affichant le résultat sur la
        sortie standard

        Précondition : L'expression en entrée doit être
        une expression valide en notation infixe
    */
    Stack *stack = init_stack();
    char c;
    bool was_operand = false;
    int read = scanf("%c", &c);
    // Tant qu'on est pas arrivé a la fin
    while (read != EOF) {
        // Tant qu'on a une opérande on l'affiche et on lit
        // le prochain caractère
        while (is_operand(c) && read != EOF) {
            printf("%c", c);
            read = scanf("%c", &c);
            was_operand = true;
        }

        // Si on avait une opérande on affiche un
        // espace pour passer au prochain opérateur
        // ou opérande
        if (was_operand)
            printf(" ");
        
        was_operand = false;
        
        // Si on est a la fin de l'expression on affiche
        // tous les opérateurs restant dans la pile
        if (c == '\n') {
            empty_stack(&stack);
            printf("\n");
        }

        // On vérifie si on est arrivé sur un opérateur
        check_operator(&stack, c);
        // On lit le prochain caractère
        read = scanf("%c", &c);
    }

    // On affiche tous les opérateurs restant dans la pile
    empty_stack(&stack);
    printf("\n");

    // On libère la mémoire prise par la pile
    delete_stack(&stack);
}

int main(void) {
    convert_2();

    return 0;
}
