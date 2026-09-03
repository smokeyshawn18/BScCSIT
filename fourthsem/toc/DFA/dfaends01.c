#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// DFA states
typedef enum { A, B, C } State;

State currentState = A;
const State finalState = C;
bool isValid = true;

// Validate input string contains only 0 and 1
void validateInput(const char input[], int length) {
    for (int i = 0; i < length; i++) {
        if (input[i] != '0' && input[i] != '1') {
            isValid = false;
            break;
        }
    }
}

// Define DFA transitions
void transition(char inputChar) {
    switch (currentState) {
        case A:
            currentState = (inputChar == '0') ? B : A;
            break;
        case B:
            currentState = (inputChar == '0') ? B : C;
            break;
        case C:
            currentState = (inputChar == '0') ? B : A;
            break;
    }
}

// Run DFA simulation
void simulateDFA(const char input[], int length) {
    currentState = A; // Reset to start state
    for (int i = 0; i < length; i++) {
        printf("Step %d → State: %c, Input: %c\n", i + 1, 'A' + currentState, input[i]);
        transition(input[i]);
    }

    if (currentState == finalState) {
        printf("\n✅ String Accepted: Ends with '01'\n");
    } else {
        printf("\n❌ String Rejected: Does not end with '01'\n");
    }
}

int main() {
    char inputString[100];

    printf("Enter a binary string: ");
    scanf("%s", inputString);  // Read input first

    int length = strlen(inputString);  // Then calculate length

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
