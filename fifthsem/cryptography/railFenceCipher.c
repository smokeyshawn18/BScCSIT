#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt_rail_fence(char *text, int rails) {
    int len = strlen(text);
    char rail[100][100] = {0};  // Rail matrix
    int row = 0, dir = 1;       // Current row and direction (1=down, -1=up)
    
    // Fill rails in zigzag pattern
    for (int i = 0; i < len; i++) {
        rail[row][i] = text[i];
        
        if (row == 0) dir = 1;           // Top rail - go down
        else if (row == rails - 1) dir = -1; // Bottom rail - go up
        
        row += dir;
    }
    
    // Read rails row by row
    int k = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j]) {
                text[k++] = rail[i][j];
            }
        }
    }
    text[k] = '\0';
}

void decrypt_rail_fence(char *cipher, int rails) {
    int len = strlen(cipher);
    char rail[100][100] = {0};
    int row = 0, dir = 1;
    
    // Mark positions in zigzag pattern
    for (int i = 0; i < len; i++) {
        rail[row][i] = '*';
        
        if (row == 0) dir = 1;
        else if (row == rails - 1) dir = -1;
        
        row += dir;
    }
    
    // Fill marked positions with cipher text
    int k = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] == '*' && k < len) {
                rail[i][j] = cipher[k++];
            }
        }
    }
    
    // Read in zigzag order
    row = 0; dir = 1;
    int idx = 0;
    for (int i = 0; i < len; i++) {
        cipher[idx++] = rail[row][i];
        
        if (row == 0) dir = 1;
        else if (row == rails - 1) dir = -1;
        
        row += dir;
    }
    cipher[idx] = '\0';
}

void prepare_text(char *text) {
    int j = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            text[j++] = toupper(text[i]);
        }
    }
    text[j] = '\0';
}

int main() {
    char text[200];
    int rails;
    
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;
    
    printf("Enter number of rails (2-10): ");
    scanf("%d", &rails);
    
    prepare_text(text);
    printf("Original: %s\n", text);
    
    // Encrypt
    char encrypted[200];
    strcpy(encrypted, text);
    encrypt_rail_fence(encrypted, rails);
    printf("Encrypted: %s\n", encrypted);
    
    // Decrypt
    char decrypted[200];
    strcpy(decrypted, encrypted);
    decrypt_rail_fence(decrypted, rails);
    printf("Decrypted: %s\n", decrypted);
    
    return 0;
}
