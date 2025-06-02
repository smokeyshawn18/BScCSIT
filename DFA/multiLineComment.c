#include <stdio.h>
#include <string.h>

int length = 0;
char finalState = 'E'; // Final state indicating comment is closed
char currentState = 'A'; // Initial state

// Function to switch states based on input character
void switchState(char inputChar) {
    switch (currentState) {
        case 'A':
            if (inputChar == '/') {
                currentState = 'B'; // First slash detected
            } else {
                currentState = 'F'; // Not a comment
            }
            break;
        case 'B':
            if (inputChar == '*') {
                currentState = 'C'; // Comment start detected
            } else {
                currentState = 'F'; // Not a comment
            }
            break;
        case 'C':
            if (inputChar == '*') {
                currentState = 'D'; // Potential end of comment
            } else {
                currentState = 'C'; // Stay inside comment
            }
            break;
        case 'D':
            if (inputChar == '/') {
                currentState = 'E'; // Comment closed
            } else if (inputChar == '*') {
                currentState = 'D'; // Stay in potential end sequence
            } else {
                currentState = 'C'; // Back inside comment
            }
            break;
        case 'E':
            // Once the comment is closed, stay in E
            currentState = 'E';
            break;
        case 'F':
            // Invalid state, not a comment
            break;
    }
}

// Function to simulate the DFA on the input string
void simulate(const char inputString[]) {
    length = strlen(inputString);
    currentState = 'A'; // Reset to initial state

    for (int i = 0; i < length; i++) {
        printf("Current State: %c, Input: '%c'\n", currentState, inputString[i]);
        switchState(inputString[i]);
    }

    // Check if the final state is reached
    if (currentState == finalState) {
        printf("✅ String Accepted: Contains a C multi-line comment /* ... */\n");
    } else {
        printf("❌ String Rejected: Does not contain a C multi-line comment\n");
    }
}

int main() {
    char inputString[] = "int main() { /* This is a multi-line comment */ return 0; }";

    printf("Shudarsan Poudel\n");
    printf("Input String:\n%s\n\n", inputString);

    simulate(inputString);

    return 0;
}
