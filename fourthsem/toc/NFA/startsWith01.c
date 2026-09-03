#include <stdio.h>
#include <string.h>

#define MAX_STATES 3
#define MAX_INPUT_LENGTH 100

// State identifiers
#define Q0 0
#define Q1 1
#define Q2 2

// Function to simulate NFA transition
// currentStates: array indicating active states (1 if active, 0 if not)
// inputChar: current input character ('0' or '1')
// nextStates: array to store next active states
void move(int currentStates[], char inputChar, int nextStates[]) {
    // Initialize nextStates to 0
    for (int i = 0; i < MAX_STATES; i++) {
        nextStates[i] = 0;
    }
    
    // Transition rules
    if (currentStates[Q0]) {
        if (inputChar == '0') {
            nextStates[Q1] = 1;
        }
    }
    
    if (currentStates[Q1]) {
        if (inputChar == '1') {
            nextStates[Q2] = 1;
        }
    }
    
    if (currentStates[Q2]) {
        // q2 loops to itself on '0' or '1'
        if (inputChar == '0' || inputChar == '1') {
            nextStates[Q2] = 1;
        }
    }
}

// Function to check if any state is the accepting state (Q2)
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
        
        // If no active state after this input, reject early
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
        printf("String accepted by the NFA (starts with 01).\n");
    } else {
        printf("String rejected by the NFA.\n");
    }
    
    return 0;
}
