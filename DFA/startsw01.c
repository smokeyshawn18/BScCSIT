#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Define DFA states
typedef enum { A, B, C, D } State;

State currentState = A;
const State finalState = C;
bool isValid = true;

// Validate input: only '0' and '1' allowed
void validateInput(const char input[], int length) {
    for (int i = 0; i < length; i++) {
        if (input[i] != '0' && input[i] != '1') {
            isValid = false;
            break;
        }
    }
}

// DFA transition logic
void transition(char inputChar) {
    switch (currentState) {
        case A:
            currentState = (inputChar == '0') ? B : D;
            break;
        case B:
            currentState = (inputChar == '1') ? C : D;
            break;
        case C:
            currentState = C; // Stay in accepting state
            break;
        case D:
            currentState = D; // Stay in rejecting state
            break;
    }
}

// Run DFA simulation
void simulateDFA(const char input[], int length) {
    currentState = A;  // Reset state
    for (int i = 0; i < length; i++) {
        printf("Step %d → State: %c, Input: %c\n", i + 1, 'A' + currentState, input[i]);
        transition(input[i]);
    }

    if (length >= 2 && currentState == C) {
        printf("\n✅ String Accepted: Starts with '01'\n");
    } else {
        printf("\n❌ String Rejected: Does not start with '01'\n");
    }
}

int main() {
    char inputString[100];
    printf("Enter a binary string: ");
    fgets(inputString, sizeof(inputString), stdin);

    // Remove newline character if present
    inputString[strcspn(inputString, "\n")] = '\0';

    int length = strlen(inputString);

    printf("Shudarsan Poudel\n");
    printf("Input String: %s\n", inputString);

    validateInput(inputString, length);

    if (isValid) {
        printf("Status: ✅ Valid binary input\n\n");
        simulateDFA(inputString, length);
    } else {
        printf("Status: ❌ Invalid input! Only 0 and 1 allowed.\n");
    }

    return 0;
}
