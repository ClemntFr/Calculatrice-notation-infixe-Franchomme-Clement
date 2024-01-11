#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000

typedef struct Stack {
    int top;
    char *a;
} Stack;

Stack * init_stack() {
    Stack *stack = (Stack*) malloc(sizeof(*stack));
    stack->top = -1;
    char *a = (char*) malloc(sizeof(char) * MAX);
    stack->a = a;

    return stack;
}

bool is_empty(Stack *pile) {
    return (pile->top == -1);
}

bool push(Stack *pile, char val) {
    if (pile->top < MAX - 1) {
        pile->a[++pile->top] = val;
        return true;
    }
    
    printf("Stack Overflow\n");
    exit(EXIT_FAILURE);
    return false;
}

char pop(Stack *pile) {
    if (pile->top < 0) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }

    return pile->a[pile->top--];
}

char peek(Stack *pile) {
    if (pile->top < 0) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }

    return pile->a[pile->top];
}

void empty_stack(Stack *stack) {
    while (!is_empty(stack)) {
        printf("%c ", pop(stack));
    }
}

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

void print_stack(Stack *pile) {
    if (is_empty(pile)) {
        printf("Stack is Empty\n");
        return;
    }

    printf("top -> ");
    for (int i = pile->top; i > 0; i--) {
        print_operator(pile->a[i]);
        printf(" | ");
    }
    print_operator(pile->a[0]);
    printf("\n");
}

int get_prio(char op) {
    if (op == '+' || op == '-')
        return 0;
    else if (op == '*' || op == '/')
        return 1;
    else if (op == '^')
        return 2;
    else
        return -1;
}

void check_prio(Stack *stack, char op) {
    if (is_empty(stack)) {
        push(stack, op);
        return ;
    }
    int prio_op = get_prio(op);
    int prio_stack = get_prio(peek(stack));

    if (prio_op > prio_stack) {
        push(stack, op);
    } else if (prio_stack >= prio_op) {
        printf("%c ", pop(stack));
        check_prio(stack, op);
    } 
}

void check_operator(Stack *stack, char op) {
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

        case 'e':
            printf("Unsupported operator encountered\n");
            exit(EXIT_FAILURE);
            break;

        case 's':
            printf("Unsupported operator encountered\n");
            exit(EXIT_FAILURE);
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
        check_operator(stack, expr[i]);
        i += 1;
    }

    empty_stack(stack);
    printf("\n");

    if (stack->a != NULL)
        free(stack->a);
    
    if (stack != NULL)
        free(stack);
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
            empty_stack(stack);
            printf("\n");
        }
        check_operator(stack, c);
        read = scanf("%c", &c);
    }

    empty_stack(stack);
    printf("\n");

    if (stack->a != NULL)
        free(stack->a);
    
    if (stack != NULL)
        free(stack);
}

int main(void) {
    convert_2();

    return 0;
}