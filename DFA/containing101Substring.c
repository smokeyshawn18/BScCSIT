#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// DFA states
typedef enum { S0, S1, S2, S3 } State;

State currentState = S0;
State finalState = S3;
bool isValid = true;
bool accepted = false; // Track if final state was ever reached

// Validate input string contains only 0 and 1
void validateInput(const char input[], int length) {
    for (int i = 0; i < length; i++) {
        if (input[i] != '0' && input[i] != '1') {
            isValid = false;
            break;
        }
    }
}

// Define state transitions
void transition(char inputChar) {
    switch (currentState) {
        case S0:
            currentState = (inputChar == '1') ? S1 : S0;
            break;
        case S1:
            currentState = (inputChar == '0') ? S2 : S1;
            break;
        case S2:
            currentState = (inputChar == '1') ? S3 : S0;
            break;
        case S3:
            currentState = (inputChar == '0') ? S2 : S1;
            break;
    }
}

// Run DFA simulation on input string
void simulateDFA(const char input[], int length) {
    for (int i = 0; i < length; i++) {
        printf("Step %d → State: S%d, Input: %c\n", i + 1, currentState, input[i]);
        transition(input[i]);
        if (currentState == finalState) {
            accepted = true;
        }
    }

    if (accepted) {
        printf("\n✅ String Accepted: Contains '101' substring\n");
    } else {
        printf("\n❌ String Rejected: Does not contain '101' substring\n");
    }
}

int main() {
    char inputString[] = "1101010"; // Example input
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

