#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generate_key_square(char *key_phrase, char key_square[5][5]) {
    char grid[25];
    int used[26] = {0};
    int idx = 0;
    
    // Add key phrase letters (I/J treated as same)
    for (int i = 0; key_phrase[i] != '\0' && idx < 25; i++) {
        char c = tolower(key_phrase[i]);
        if (c == 'j') c = 'i';  // Playfair rule: I/J same
        int pos = c - 'a';
        if (pos >= 0 && pos < 26 && pos != 9 && !used[pos]) {  // Skip J
            grid[idx++] = 'a' + pos;
            used[pos] = 1;
        }
    }
    
    // Fill with remaining alphabet (skip J)
    for (int i = 0; i < 26 && idx < 25; i++) {
        if (i != 9 && !used[i]) {  // Skip J
            grid[idx++] = 'a' + i;
            used[i] = 1;
        }
    }
    
    // Fill 5x5 grid
    int k = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            key_square[i][j] = grid[k++];
        }
    }
}

void find_position(char c, char key_square[5][5], int *row, int *col) {
    if (tolower(c) == 'j') c = 'i';
    char lc = tolower(c);
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (key_square[i][j] == lc) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void prepare_text(char *text) {
    // Convert to uppercase, remove non-letters, add X padding, split double letters
    char result[200] = {0};
    int j = 0;
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            result[j++] = toupper(text[i]);
        }
    }
    
    // Split double letters and pad with X
    for (int i = 0; i < j; i++) {
        if (i < j - 1 && result[i] == result[i+1]) {
            result[i+1] = 'X';
            i++;  // Skip next char
        }
    }
    
    // Pad to even length
    if (j % 2 != 0) {
        result[j++] = 'X';
    }
    
    strcpy(text, result);
}

void encrypt(char text[], char key_square[5][5]) {
    prepare_text(text);
    
    for (int i = 0; i < strlen(text); i += 2) {
        int row1, col1, row2, col2;
        find_position(text[i], key_square, &row1, &col1);
        find_position(text[i+1], key_square, &row2, &col2);
        
        if (row1 == row2) {  // Same row: shift right
            text[i] = key_square[row1][(col1 + 1) % 5];
            text[i+1] = key_square[row2][(col2 + 1) % 5];
        }
        else if (col1 == col2) {  // Same column: shift down
            text[i] = key_square[(row1 + 1) % 5][col1];
            text[i+1] = key_square[(row2 + 1) % 5][col2];
        }
        else {  // Rectangle: swap columns
            text[i] = key_square[row1][col2];
            text[i+1] = key_square[row2][col1];
        }
    }
}

void decrypt(char text[], char key_square[5][5]) {
    for (int i = 0; i < strlen(text); i += 2) {
        int row1, col1, row2, col2;
        find_position(text[i], key_square, &row1, &col1);
        find_position(text[i+1], key_square, &row2, &col2);
        
        if (row1 == row2) {  // Same row: shift left
            text[i] = key_square[row1][(col1 + 4) % 5];
            text[i+1] = key_square[row2][(col2 + 4) % 5];
        }
        else if (col1 == col2) {  // Same column: shift up
            text[i] = key_square[(row1 + 4) % 5][col1];
            text[i+1] = key_square[(row2 + 4) % 5][col2];
        }
        else {  // Rectangle: swap columns
            text[i] = key_square[row1][col2];
            text[i+1] = key_square[row2][col1];
        }
    }
    // Remove padding X's (simple version)
    for (int i = strlen(text) - 1; i > 0; i--) {
        if (text[i] == 'X' && (i == strlen(text) - 1 || !isalpha(text[i-1]))) {
            text[i] = '\0';
        } else {
            break;
        }
    }
}

void print_key_square(char key_square[5][5]) {
    printf("Key Square:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", key_square[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    char text[200];
    char key_square[5][5];
    char key_phrase[50];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;  // Remove newline

    printf("Enter key phrase: ");
    scanf("%s", key_phrase);

    generate_key_square(key_phrase, key_square);
    print_key_square(key_square);

    // Encrypt
    char encrypted[200];
    strcpy(encrypted, text);
    encrypt(encrypted, key_square);
    printf("Encrypted: %s\n", encrypted);

    // Decrypt
    decrypt(encrypted, key_square);
    printf("Decrypted: %s\n", encrypted);

    return 0;
}
