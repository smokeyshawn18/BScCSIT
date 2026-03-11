#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void generate_random_key(char *key, int length) {
    srand(time(NULL));
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    for (int i = 0; i < length; i++) {
        key[i] = charset[rand() % 26];
    }
    key[length] = '\0';
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

void encrypt(char *text, char *key) {
    prepare_text(text);
    int len = strlen(text);
    
    for (int i = 0; i < len; i++) {
        text[i] = ((text[i] - 'A') ^ (key[i] - 'A')) + 'A';
    }
}

void decrypt(char *text, char *key) {
    prepare_text(text);
    int len = strlen(text);
    
    for (int i = 0; i < len; i++) {
        text[i] = ((text[i] - 'A') ^ (key[i] - 'A')) + 'A';
    }
}

int main() {
    char text[200];
    char key[200];
    int key_len;
    
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;
    
    printf("Enter key length (same as text length): ");
    scanf("%d", &key_len);
    
    // Generate random one-time key
    generate_random_key(key, key_len);
    printf("Generated One-Time Key: %s\n", key);
    
    // Encrypt
    char encrypted[200];
    strcpy(encrypted, text);
    encrypt(encrypted, key);
    printf("Encrypted: %s\n", encrypted);
    
    // Decrypt
    char decrypted[200];
    strcpy(decrypted, encrypted);
    decrypt(decrypted, key);
    printf("Decrypted: %s\n", decrypted);
    
    printf("\nWARNING: One-Time Pad keys must be truly random and used only once!\n");
    
    return 0;
}
