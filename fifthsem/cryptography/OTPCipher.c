#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char message[200];
    unsigned char key[200], cipher[200], decrypted[200];

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;

    int len = strlen(message);

    srand(time(NULL));  // Initialize random generator

    // Generate key and encrypt
    for(int i = 0; i < len; i++) {
        key[i] = rand() % 256;                 // random byte (0–255)
        cipher[i] = message[i] ^ key[i];       // encryption
    }

    // Display input (ASCII)
    printf("\nUser input (ASCII): ");
    for(int i = 0; i < len; i++)
        printf("%d ", message[i]);

    // Display key
    printf("\nRandom key: ");
    for(int i = 0; i < len; i++)
        printf("%d ", key[i]);

    // Display encrypted
    printf("\nEncrypted: ");
    for(int i = 0; i < len; i++)
        printf("%d ", cipher[i]);

    // Decryption
    for(int i = 0; i < len; i++) {
        decrypted[i] = cipher[i] ^ key[i];
    }
    decrypted[len] = '\0';

    // Display decrypted text
    printf("\nDecrypted: %s\n", decrypted);

    printf("\nWARNING: OTP key must be random and used only once!\n");

    return 0;
}