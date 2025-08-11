#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STACK_SIZE 1000

// Stack structure
typedef struct {
    char data[STACK_SIZE];
    int top;
} Stack;

// Initialize stack with bottom marker
void initStack(Stack* s) {
    s->top = -1;
}

// Push symbol to stack
void push(Stack* s, char c) {
    if (s->top < STACK_SIZE - 1) {
        s->data[++s->top] = c;
    } else {
        printf("Stack overflow\n");
    }
}

// Pop symbol from stack; returns '\0' if empty
char pop(Stack* s) {
    if (s->top >= 0) {
        return s->data[s->top--];
    }
    return '\0';
}

// Check if stack is empty
bool isEmpty(Stack* s) {
    return s->top == -1;
}

// Validate input string (only 0 and 1)
bool isValidInput(const char* str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] != '0' && str[i] != '1') return false;
    }
    return true;
}

int main() {
    char input[STACK_SIZE];
    Stack stack;
    int countZero = 0;  // count of 0's
    int countOne = 0;   // count of 1's

    printf("Shudarsan Poudel\n");
    printf("Enter the string: ");
    scanf("%s", input);

    if (!isValidInput(input)) {
        printf("Invalid input: only '0' and '1' allowed.\n");
        return 1;
    }

    initStack(&stack);

    int i = 0;
    int length = strlen(input);

    // Step 1: Read all 0's and push
    while (i < length && input[i] == '0') {
        push(&stack, 'Z');
        countZero++;
        i++;
    }

    // Reject if no 0's or only one 0 (since n > 1)
    if (countZero <= 1) {
        printf("String rejected: number of 0's should be > 1.\n");
        return 0;
    }

    // Step 2: Read 1's and pop
    while (i < length && input[i] == '1') {
        char popped = pop(&stack);
        if (popped == '\0') {
            // No matching 0 for this 1
            printf("String rejected: More 1's than 0's.\n");
            return 0;
        }
        countOne++;
        i++;
    }

    // Reject if not all input consumed or number of ones <= 1
    if (i != length) {
        printf("String rejected: Invalid characters after 0^n 1^n pattern.\n");
        return 0;
    }
    if (countOne <= 1) {
        printf("String rejected: number of 1's should be > 1.\n");
        return 0;
    }

    // Final check: stack should be empty to have equal number 0's and 1's
    if (isEmpty(&stack)) {
        printf("String accepted\n");
    } else {
        printf("String rejected: Number of 0's and 1's not equal.\n");
    }

    return 0;
}
