#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// DFA states
typedef enum { A, B, C, D } State;

State currentState = A; // Initial state
State finalState = C;   // Final state indicating a valid comment

// Function to switch states based on input character
void switchState(char inputChar) {
    switch (currentState) {
        case A:
            if (inputChar == '/') {
                currentState = B; // First slash detected
            } else {
                currentState = D; // Not a comment
            }
            break;
        case B:
            if (inputChar == '/') {
                currentState = C; // Second slash detected, comment starts
            } else {
                currentState = D; // Not a comment
            }
            break;
        case C:
            // Stay in C as long as we are inside the comment
            break;
        case D:
            // Once in D, we are outside of a comment
            break;
    }
}

// Function to simulate the DFA on the input string
void simulate(const char inputString[]) {
    int length = strlen(inputString);
    
    for (int i = 0; i < length; i++) {
        printf("Current State: %c, Input: '%c'\n", 'A' + currentState, inputString[i]);
        switchState(inputString[i]);
    }

    // Check if the final state is reached
    if (currentState == finalState) {
        printf("✅ String Accepted: Contains a C single-line comment\n");
    } else {
        printf("❌ String Rejected: Does not contain a C single-line comment\n");
    }
}

int main() {
    char inputString[100];

    printf("Enter a C single-line comment (e.g., // This is a comment): ");
    fgets(inputString, sizeof(inputString), stdin);
    printf("Shudarsan Poudel\n");
    printf("Input String:\n%s\n", inputString);
    
    simulate(inputString);
    
    return 0;
}
