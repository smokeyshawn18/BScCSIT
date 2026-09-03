#include <stdio.h>
#include <string.h>

// DFA states using enum
typedef enum { A, B, C, D, E, F } State;

State currentState = A;            // Initial state
const State finalState = E;        // Final accepting state

// Function to switch states based on input character
void switchState(char inputChar) {
    switch (currentState) {
        case A:
            if (inputChar == '/')
                currentState = B;
            else
                currentState = F;
            break;

        case B:
            if (inputChar == '*')
                currentState = C;
            else
                currentState = F;
            break;

        case C:
            if (inputChar == '*')
                currentState = D;
            // else stay in C
            break;

        case D:
            if (inputChar == '/')
                currentState = E;
            else if (inputChar != '*')
                currentState = C;
            // else stay in D
            break;

        case E:
            // Final state, remain here
            break;

        case F:
            // Invalid comment, remain here
            break;
    }
}

// Function to simulate the DFA on the input string
void simulate(const char inputString[]) {
    int length = strlen(inputString);
    currentState = A; // Reset state for each simulation

    for (int i = 0; i < length; i++) {
        printf("Current State: %c, Input: '%c'\n", 'A' + currentState, inputString[i]);
        switchState(inputString[i]);
    }

    // Check if we reached the final state
    if (currentState == finalState) {
        printf("✅ String Accepted: Contains a C multi-line comment\n");
    } else {
        printf("❌ String Rejected: Does not contain a valid C multi-line comment\n");
    }
}

int main() {
    char inputString[200];

    printf("Enter a C multi-line comment (e.g., /* This is a comment */): ");
    fgets(inputString, sizeof(inputString), stdin);

    printf("Shudarsan Poudel\n");
    printf("Input String:\n%s\n", inputString);

    simulate(inputString);

    return 0;
}
