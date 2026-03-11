#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 3
#define MOD 26

void getKeyMatrix(char *key, int keyMatrix[SIZE][SIZE]) {
    int k = 0, i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            while (!isalpha(key[k])) k++;
            keyMatrix[i][j] = toupper(key[k++]) - 'A';
        }
    }
}

void matrixMultiply(int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int result[SIZE][SIZE]) {
    int i, j, k;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (k = 0; k < SIZE; k++) {
                result[i][j] = (result[i][j] + mat1[i][k] * mat2[k][j]) % MOD;
            }
        }
    }
}

void encrypt(char message[], int keyMatrix[SIZE][SIZE], char cipher[]) {
    int msgVector[SIZE][1], cipherVector[SIZE][1];
    int i, len = strlen(message);
    
    strcpy(cipher, message);
    
    for (i = 0; i < len; i += SIZE) {
        int j;
        for (j = 0; j < SIZE; j++) {
            if (i + j < len) {
                msgVector[j][0] = toupper(cipher[i+j]) - 'A';
            } else {
                msgVector[j][0] = 0; // pad with A
            }
        }
        
        int x;
        for (x = 0; x < SIZE; x++) {
            cipherVector[x][0] = 0;
            int y;
            for (y = 0; y < SIZE; y++) {
                cipherVector[x][0] = (cipherVector[x][0] + keyMatrix[x][y] * msgVector[y][0]) % MOD;
            }
        }
        
        for (j = 0; j < SIZE; j++) {
            cipher[i+j] = cipherVector[j][0] + 'A';
        }
    }
    cipher[len] = '\0';
}

void decrypt(char cipher[], int keyMatrix[SIZE][SIZE], char message[]) {
    int invMatrix[SIZE][SIZE];
    
    // Simple 3x3 inverse calculation (determinant must be coprime with 26)
    int det = (keyMatrix[0][0]*(keyMatrix[1][1]*keyMatrix[2][2] - keyMatrix[1][2]*keyMatrix[2][1]) -
               keyMatrix[0][1]*(keyMatrix[1][0]*keyMatrix[2][2] - keyMatrix[1][2]*keyMatrix[2][0]) +
               keyMatrix[0][2]*(keyMatrix[1][0]*keyMatrix[2][1] - keyMatrix[1][1]*keyMatrix[2][0]));
    
    int detInv = 0;
    for (int i = 1; i < MOD; i++) {
        if ((det * i) % MOD == 1) {
            detInv = i;
            break;
        }
    }
    
    // Adjugate matrix (simplified for demo)
    invMatrix[0][0] = ((keyMatrix[1][1]*keyMatrix[2][2] - keyMatrix[1][2]*keyMatrix[2][1]) * detInv) % MOD;
    invMatrix[0][1] = ((keyMatrix[0][2]*keyMatrix[2][1] - keyMatrix[0][1]*keyMatrix[2][2]) * detInv) % MOD;
    invMatrix[1][0] = ((keyMatrix[1][2]*keyMatrix[2][0] - keyMatrix[1][0]*keyMatrix[2][2]) * detInv) % MOD;
    invMatrix[1][1] = ((keyMatrix[0][0]*keyMatrix[2][2] - keyMatrix[0][2]*keyMatrix[2][0]) * detInv) % MOD;
    
    int len = strlen(cipher);
    strcpy(message, cipher);
    
    for (int i = 0; i < len; i += SIZE) {
        int msgVector[SIZE][1], plainVector[SIZE][1];
        int j;
        for (j = 0; j < SIZE; j++) {
            msgVector[j][0] = toupper(message[i+j]) - 'A';
        }
        
        int x;
        for (x = 0; x < SIZE; x++) {
            plainVector[x][0] = 0;
            int y;
            for (y = 0; y < SIZE; y++) {
                plainVector[x][0] = (plainVector[x][0] + invMatrix[x][y] * msgVector[y][0]) % MOD;
            }
        }
        
        for (j = 0; j < SIZE; j++) {
            message[i+j] = plainVector[j][0] + 'A';
        }
    }
}

void printMatrix(int matrix[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    char text[100], key[20] = "GYBNQKURP", encrypted[100], decrypted[100];
    int keyMatrix[SIZE][SIZE];
    
    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;
    
    printf("Key (9 chars, default GYBNQKURP): ");
    scanf("%s", key);
    
    getKeyMatrix(key, keyMatrix);
    printf("Key Matrix:\n");
    printMatrix(keyMatrix);
    
    encrypt(text, keyMatrix, encrypted);
    printf("Encrypted: %s\n", encrypted);
    
    decrypt(encrypted, keyMatrix, decrypted);
    printf("Decrypted: %s\n", decrypted);
    
    return 0;
}
