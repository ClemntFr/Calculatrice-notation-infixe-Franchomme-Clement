#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pile.h"

#define SUPPORTED_MODS "hc"
#define OPERATORS "+-*/^es()"
#define OPERANDS ".0123456789"


typedef struct Mod {
    char end;
    char separator;
} Mod;


bool is_in(char a, char *tab) {
    /* 
        Renvoie true si un caractère est 
        dans une chaine de caractères,
        false sinon
    */
    for (int i = 0; tab[i] != '\0'; i++) {
        if (tab[i] == a) return true;
    }

    return false;
}

bool is_supported_mod(char *mod) {
    /*
        Vérifie que le flag entré par l'utilisateur est valide si il y en a un 
    */
    if (strlen(mod) != 2 || mod[0] != '-' || !is_in(mod[1], SUPPORTED_MODS)) {
        printf("Veuillez entrer un mode d'affichage valide :\n");
        printf("\t-h pour une sortie lisible (mode de déboggage)\n");
        printf("\t-c pour une sortie destinée a l'ordinateur\n");
        return false;
    }
    return true;
}

Mod bind_mod(char mod) {
    if (mod == 'h') {
        return (Mod) {'\n', ' '};   
    } else if (mod == 'c') {
        return (Mod) {';', '\n'};
    } else
        return (Mod) {0, 0};
}

bool is_operator(char op) {
    /*
        Renvoie true si le caractère d'entrée
        est un opérateur connu, false sinon
    */
    return is_in(op, OPERATORS); 
}

bool is_operand(char op) {
    /*
        Renvoie true si le caractère d'entrée
        est une opérande connue
    */
    return is_in(op, OPERANDS);
}

void print_operator(char op, char separator) {
    /*
        Affiche chaque opérateur 
        de manière a pouvoir l'évaluer
    */
    if (op == 'e')
        printf("exp%c", separator);
    else if (op == 's')
        printf("sqrt%c", separator);
    else
        printf("%c%c", op, separator);
}

/* Affiche tout ce qui est dans la pile séparé par le */
/* caractère separator jusqu'a ce que le dernier élément soit atteint */
void empty_stack(Stack **stack, char separator) {
    while (!is_empty(*stack)) {
        print_operator(pop(stack), separator);
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

void compare_prio_wstack(Stack **stack, char op, char separator) {
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
        print_operator(pop(stack), separator);
        compare_prio_wstack(stack, op, separator);
    } 
}

void comp_operator_wstack(Stack **stack, char op, char separator) {
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
                print_operator(top, separator);
                top = pop(stack);
            }
            break;
        
        default:
            compare_prio_wstack(stack, op, separator);
            break;
        }
    }
}

void print_endline(char end) {
    /*
        Permet d'éviter de faire un retour a la ligne de trop
        en mode humain
    */
    if (end == '\n')
        printf("\n");
    else
        printf("%c\n", end);
}

void convert_stdin(char mod_input) {
    /*
        Convertit une expression en notation infixe
        entrée sur l'entrée standard en notation 
        postfixe. Affiche le résultat sur la
        sortie standard

        Précondition : L'expression en entrée doit être
        une expression valide en notation infixe
    */
    Mod mod = bind_mod(mod_input);

    Stack *stack = init_stack();
    char c;
    bool was_operand = false;

    while (scanf("%c", &c) != EOF && c != 'q') {
        if (is_operand(c)) {
            printf("%c", c);
            was_operand = true;
        } 
        else if (c == '\n') {
            printf("%c", mod.separator * was_operand);
            empty_stack(&stack, mod.separator);
            print_endline(mod.end);
        }
        else {
            printf("%c", mod.separator * was_operand);
            was_operand = false;

            comp_operator_wstack(&stack, c, mod.separator);
        }
    }

    // On affiche tous les opérateurs restant dans la pile sans la supprimer
    empty_stack(&stack, mod.separator);
    print_endline(mod.end);

    delete_stack(&stack);
}


int main(int argc, char *argv[]) {
    // Si on a pas de flag on ce met en mode ordinateur
    if (argc < 2) {
        convert_stdin('c');
        return 0;
    }
    if (!is_supported_mod(argv[1])) { 
        return -1; 
    }

    convert_stdin(argv[1][1]);
    return 0;
}
