#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pile.h"

bool is_in(char a, char *tab) {
    int i = 0;
    while(tab[i] != '\0') {
        if (tab[i] == a)
            return true;
        i += 1;
    }
    
    return false;
}

bool is_operator(char op) {
    char operators[] = "+-*/^es()";
    return is_in(op, operators); 
}

bool is_operand(char op) {
    char operands[] = ".0123456789";
    return is_in(op, operands);
}

void print_operator(char op) {
    if (op == 'e')
        printf("exp ");
    else if (op == 's')
        printf("sqrt ");
    else
        printf("%c ", op);
}


int get_prio(char op) {
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
    if (is_empty(*stack)) {
        push(stack, op);
        return ;
    }
    int prio_op = get_prio(op);
    int prio_stack = get_prio(peek(*stack));

    if (prio_op > prio_stack) {
        push(stack, op);
    } else if (prio_stack >= prio_op) {
        print_operator(pop(stack));
        check_prio(stack, op);
    } 
}

void check_operator(Stack **stack, char op) {
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
    Stack *stack = init_stack();
    int i = 0;
    while (expr[i] != '\0') {
        if (is_operand(expr[i])) {
            while(is_operand(expr[i]))
                printf("%c", expr[i++]);
            printf(" ");
        }
        check_operator(&stack, expr[i]);
        i += 1;
    }

    empty_stack(&stack);
    printf("\n");

    delete_stack(&stack);
}

void convert_2() {
    Stack *stack = init_stack();
    char c;
    bool was_operand = false;
    int read = scanf("%c", &c);
    while (read != EOF) {
        while (is_operand(c) && read != EOF) {
            printf("%c", c);
            read = scanf("%c", &c);
            was_operand = true;
        }
        if (was_operand)
            printf(" ");
        
        was_operand = false;
        
        if (c == '\n') {
            empty_stack(&stack);
            printf("\n");
        }
        check_operator(&stack, c);
        read = scanf("%c", &c);
    }

    empty_stack(&stack);
    printf("\n");

    delete_stack(&stack);
}

int main(void) {
    convert_2();

    return 0;
}
