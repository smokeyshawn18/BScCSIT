#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STACK_SIZE 1000

// Stack structure
typedef struct {
    char data[STACK_SIZE];
    int top;
} Stack;

// Initialize stack with Z0 symbol at bottom
void initStack(Stack* s) {
    s->top = 0;
    s->data[s->top] = 'Z';  // Z0 bottom symbol
}

// Push symbol onto stack
void push(Stack* s, char ch) {
    if (s->top < STACK_SIZE - 1) {
        s->top++;
        s->data[s->top] = ch;
    } else {
        printf("Stack overflow\n");
    }
}

// Pop symbol from stack
char pop(Stack* s) {
    if (s->top > 0) {  // don't pop bottom symbol Z0
        char ch = s->data[s->top];
        s->top--;
        return ch;
    } else {
        return '\0';  // empty or only bottom symbol
    }
}

// Peek top element of stack
char peek(Stack* s) {
    if (s->top >= 0) {
        return s->data[s->top];
    }
    return '\0';
}

// Check if stack only has bottom symbol 'Z'
bool isStackEmpty(Stack* s) {
    return (s->top == 0 && s->data[s->top] == 'Z');
}

// Check if input string has only 0 and 1
bool isValidInput(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }
    return true;
}

int main() {
    char input[STACK_SIZE];
    Stack stack;
    
    printf("Shudarsan Poudel\n");
    printf("Enter binary string over {0,1}: ");
    scanf("%s", input);
    
    if (!isValidInput(input)) {
        printf("Invalid input: only '0' and '1' allowed.\n");
        return 1;
    }
    
    initStack(&stack);

    // Simulate PDA transitions on input
    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];
        char top = peek(&stack);
        
        if (ch == '0') {
            if (top == '1') {
                pop(&stack);  // pop an unmatched '1' to balance
            } else {
                push(&stack, '0');  // push unmatched '0'
            }
        } else if (ch == '1') {
            if (top == '0') {
                pop(&stack);  // pop an unmatched '0' to balance
            } else {
                push(&stack, '1');  // push unmatched '1'
            }
        }
    }
    
    if (isStackEmpty(&stack)) {
        printf("String accepted by the PDA (equal number of 0's and 1's).\n");
    } else {
        printf("String rejected by the PDA (unequal number of 0's and 1's).\n");
    }
    
    return 0;
}
