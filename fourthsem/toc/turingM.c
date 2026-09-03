#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TAPE_SIZE 100

// Tape symbols
#define BLANK '_'
#define ZERO '0'
#define ONE '1'
#define X_MARK 'X' // Marked zero
#define Y_MARK 'Y' // Marked one

// States of the Turing Machine
typedef enum {
    START,      // initial state
    FIND_RIGHT_ONE,  // find rightmost unmarked 1
    RETURN_LEFT,     // move back to leftmost unmarked 0
    CHECK_DONE,      // check if all done
    ACCEPT,
    REJECT
} State;

void printTape(char tape[], int head, int length) {
    for (int i = 0; i < length; i++) {
        if (i == head)
            printf("[%c]", tape[i]);
        else
            printf(" %c ", tape[i]);
    }
    printf("\n");
}

// Function simulating the TM
void simulateTM(char tape[], int length) {
    int head = 0;
    State state = START;
    int zeroCount = 0;
    int oneCount = 0;

    // Input constraints: at least n>1 zeros and ones
    // We rely on TM logic to accept/reject based on matching.

    while (state != ACCEPT && state != REJECT) {
        // For debugging, you can uncomment below line:
        // printTape(tape, head, length);

        switch (state) {
            case START:
                // Find leftmost unmarked 0 to mark
                if (head >= length) {
                    // No unmarked 0 found, go check done
                    state = CHECK_DONE;
                    head = 0; // move tape head to start
                } else if (tape[head] == ZERO) {
                    tape[head] = X_MARK;  // mark visited 0
                    // Move right to find corresponding 1
                    state = FIND_RIGHT_ONE;
                    head++;
                } else {
                    head++;
                }
                break;

            case FIND_RIGHT_ONE:
                if (head >= length) {
                    // Reached end of tape without finding unmarked 1 → reject
                    state = REJECT;
                } else if (tape[head] == ONE) {
                    // Mark this 1
                    tape[head] = Y_MARK;
                    // Move back to start to find next 0
                    state = RETURN_LEFT;
                    head--;
                } else {
                    head++;
                }
                break;

            case RETURN_LEFT:
                if (head < 0) {
                    // Back at the left end, start next cycle
                    head = 0;
                    state = START;
                } else if (tape[head] == ZERO || tape[head] == X_MARK) {
                    // Move left
                    head--;
                } else {
                    head--;
                }
                break;

            case CHECK_DONE:
                // Check if any unmarked 0 or unmarked 1 remains
                {
                    bool zeroLeft = false, oneLeft = false;
                    for (int i = 0; i < length; i++) {
                        if (tape[i] == ZERO) zeroLeft = true;
                        if (tape[i] == ONE) oneLeft = true;
                    }
                    // Accept if no zeros or ones left unmarked and n > 1
                    // Check n > 1 by counting marked symbols
                    int markedZero = 0, markedOne = 0;
                    for (int i = 0; i < length; i++) {
                        if (tape[i] == X_MARK) markedZero++;
                        if (tape[i] == Y_MARK) markedOne++;
                    }
                    if (!zeroLeft && !oneLeft 
                        && markedZero == markedOne 
                        && markedZero > 1) {
                        state = ACCEPT;
                    } else {
                        state = REJECT;
                    }
                }
                break;

            default:
                state = REJECT; // safety fallback
                break;
        }
    }

    if (state == ACCEPT) {
        printf("Input string ACCEPTED by the Turing Machine (belongs to 0^n1^n with n > 1).\n");
    } else {
        printf("Input string REJECTED by the Turing Machine.\n");
    }
}

int main() {
    char input[TAPE_SIZE];

    printf("Enter input string over {0,1} (format 0^n1^n with n>1): ");
    scanf("%s", input);

    // Validate input: only 0 and 1 allowed
    int length = (int)strlen(input);
    for (int i = 0; i < length; i++) {
        if (input[i] != ZERO && input[i] != ONE) {
            printf("Error: Invalid character %c detected. Only 0 and 1 allowed.\n", input[i]);
            return 1;
        }
    }

    // Copy input to tape with blanks at end
    char tape[TAPE_SIZE];
    for (int i = 0; i < length; i++) {
        tape[i] = input[i];
    }
    // Fill rest with blanks
    for (int i = length; i < TAPE_SIZE; i++) {
        tape[i] = BLANK;
    }

    // Simulate TM
    simulateTM(tape, length);

    return 0;
}
