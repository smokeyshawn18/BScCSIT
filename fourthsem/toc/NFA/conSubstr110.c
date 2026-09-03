#include <stdio.h>
#include <string.h>

#define MAX_STATES 4
#define MAX_INPUT_LENGTH 100

// State identifiers
#define Q0 0  // start state, no match
#define Q1 1  // matched '0'
#define Q2 2  // matched "01"
#define Q3 3  // matched "010" (accepting)

// Function to simulate NFA transitions for one input character
void move(int currentStates[], char inputChar, int nextStates[]) {
    // Clear nextStates
    for (int i = 0; i < MAX_STATES; i++)
        nextStates[i] = 0;

    // From Q0
    if (currentStates[Q0]) {
        if (inputChar == '0') nextStates[Q1] = 1;
        if (inputChar == '1') nextStates[Q0] = 1;
    }
    // From Q1
    if (currentStates[Q1]) {
        if (inputChar == '0') nextStates[Q1] = 1; // stay in Q1
        if (inputChar == '1') nextStates[Q2] = 1;
    }
    // From Q2
    if (currentStates[Q2]) {
        if (inputChar == '0') nextStates[Q3] = 1; // matched "010"
        if (inputChar == '1') nextStates[Q0] = 1; // fail, restart
    }
    // From Q3 (accepting)
    if (currentStates[Q3]) {
        // stay in Q3 for any input once matched
        if (inputChar == '0' || inputChar == '1') nextStates[Q3] = 1;
    }
}

// Check if any accepting state (Q3) is active
int isAccepted(int currentStates[]) {
    return currentStates[Q3];
}

int main() {
    char input[MAX_INPUT_LENGTH];
    printf("Shudarsan Poudel\n");
    printf("Enter a binary string over {0,1}: ");
    scanf("%s", input);

    int currentStates[MAX_STATES] = {0};
    int nextStates[MAX_STATES] = {0};

    currentStates[Q0] = 1; // start state active

    int length = strlen(input);
    int i;
    for (i = 0; i < length; i++) {
        move(currentStates, input[i], nextStates);
        for (int j = 0; j < MAX_STATES; j++)
            currentStates[j] = nextStates[j];

        // Early rejection if no active states
        int noneActive = 1;
        for (int j = 0; j < MAX_STATES; j++) {
            if (currentStates[j]) {
                noneActive = 0;
                break;
            }
        }
        if (noneActive) break;
    }

    if (i == length && isAccepted(currentStates)) {
        printf("String accepted by the NFA (contains substring \"010\").\n");
    } else {
        printf("String rejected by the NFA.\n");
    }

    return 0;
}
