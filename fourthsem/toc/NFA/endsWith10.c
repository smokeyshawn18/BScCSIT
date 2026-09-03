#include <stdio.h>
#include <string.h>

#define MAX_STATES 3
#define MAX_INPUT_LENGTH 100

// State identifiers
#define Q0 0  // Start state
#define Q1 1  // Seen '1'
#define Q2 2  // Accepted "10"

// Function to simulate NFA transitions for one input character
void move(int currentStates[], char inputChar, int nextStates[]) {
    // Clear next states
    for (int i = 0; i < MAX_STATES; i++) {
        nextStates[i] = 0;
    }

    // From Q0
    if (currentStates[Q0]) {
        if (inputChar == '1') {
            nextStates[Q1] = 1;
        } else if (inputChar == '0') {
            nextStates[Q0] = 1; // remain in Q0
        }
    }

    // From Q1
    if (currentStates[Q1]) {
        if (inputChar == '0') {
            nextStates[Q2] = 1; // complete "10"
        } else if (inputChar == '1') {
            nextStates[Q1] = 1; // stay in Q1
        }
    }

    // From Q2
    if (currentStates[Q2]) {
        if (inputChar == '0') {
            nextStates[Q0] = 1;
        } else if (inputChar == '1') {
            nextStates[Q1] = 1;
        }
    }
}

// Function to check if any active state is the accepting state Q2
int isAccepted(int currentStates[]) {
    return currentStates[Q2];
}

int main() {
    char input[MAX_INPUT_LENGTH];
    printf("Shudarsan Poudel\n");
    printf("Enter a binary string over {0,1}: ");
    scanf("%s", input);

    int currentStates[MAX_STATES] = {0};
    int nextStates[MAX_STATES] = {0};

    // Start with initial state Q0 active
    currentStates[Q0] = 1;

    int length = strlen(input);
    int i;
    for (i = 0; i < length; i++) {
        move(currentStates, input[i], nextStates);

        // Copy nextStates to currentStates
        for (int j = 0; j < MAX_STATES; j++) {
            currentStates[j] = nextStates[j];
        }

        // Check if no active state, reject early
        int noneActive = 1;
        for (int j = 0; j < MAX_STATES; j++) {
            if (currentStates[j] == 1) {
                noneActive = 0;
                break;
            }
        }
        if (noneActive) {
            break;
        }
    }

    if (i == length && isAccepted(currentStates)) {
        printf("String accepted by the NFA (ends with 10).\n");
    } else {
        printf("String rejected by the NFA.\n");
    }

    return 0;
}
