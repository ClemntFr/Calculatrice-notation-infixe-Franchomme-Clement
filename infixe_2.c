#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

void print_operator(char op, char space) {
    /*
        Affiche chaque opérateur 
        de manière a pouvoir l'évaluer
    */
    if (op == 'e')
        printf("exp%c", space);
    else if (op == 's')
        printf("sqrt%c", space);
    else
        printf("%c%c", op, space);
}

/* Affiche tout ce qui est dans la pile séparé par le */
/* caractère space jusqu'a ce que le dernier élément soit atteint */
void empty_stack(Stack **stack, char space) {
    while (!is_empty(*stack)) {
        print_operator(pop(stack), space);
    }
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

void check_prio(Stack **stack, char op, char space) {
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
        print_operator(pop(stack), space);
        check_prio(stack, op, space);
    } 
}

void check_operator(Stack **stack, char op, char space) {
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
                print_operator(top, space);
                top = pop(stack);
            }
            break;
        
        default:
            check_prio(stack, op, space);
            break;
        }
    }
}

int check_operand(char *c, int read, char space) {
    if (is_operand(*c)) {
        while (is_operand(*c) && read != EOF) {
            printf("%c", *c);
            read = scanf("%c", c);
        }
        printf("%c", space);
    }
    return read;
}

void convert(char mod) {
    /*
        Convertit une expression en notation infixe
        entrée sur l'entrée standard en notation 
        postfixe en affichant le résultat sur la
        sortie standard

        Précondition : L'expression en entrée doit être
        une expression valide en notation infixe
    */
    char end = '\n';
    char space = ' ';
    if (mod == 'c') {
        end = ';';
        space = '\n';
    }
    Stack *stack = init_stack();
    char c;
    bool was_operand = false;
    int read = scanf("%c", &c);
    // Tant qu'on est pas arrivé a la fin
    while (read != EOF) {
        // Tant qu'on a une opérande on l'affiche et on lit
        // le prochain caractère
        read = check_operand(&c, read, space);
        
        // Si on est a la fin de l'expression on affiche
        // tous les opérateurs restant dans la pile
        if (c == '\n') {
            empty_stack(&stack, space);
            (end ==  '\n')? printf("\n") : printf("%c\n", end);
        }

        // On vérifie si on est arrivé sur un opérateur
        check_operator(&stack, c, space);
        // On lit le prochain caractère
        read = scanf("%c", &c);
    }

    // On affiche tous les opérateurs restant dans la pile
    empty_stack(&stack, space);
    (end ==  '\n')? printf("\n") : printf("%c\n", end);

    // On libère la mémoire prise par la pile
    delete_stack(&stack);
}

bool is_supported_mod(char *mod) {
    /* Vérifie que le flag entré par l'utilisateur est valide si il y en a un */
    char supported_mods[] = "hc";
    if (strlen(mod) < 2 || mod[0] != '-' || !is_in(mod[1], supported_mods)) {
        printf("Veuillez entrer un mode d'affichage valide :\n");
        printf("\t-h pour une sortie lisible (mode de déboggage)\n");
        printf("\t-c pour une sortie destinée a l'ordinateur\n");
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    // Si on a pas de flag on ce met en mode ordinateur
    if (argc < 2) {
        convert('c');
        return 0;
    }
    // Sinon on vérifie le flag
    if (!is_supported_mod(argv[1])) { 
        return -1; 
    }
    // Si il est valide on l'utilise
    convert(argv[1][1]);
    return 0;
}
