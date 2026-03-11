#include <stdio.h>
#include <string.h>
#include <ctype.h>

void prepare_text(char *text) {
    int j = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            text[j++] = toupper(text[i]);
        }
    }
    text[j] = '\0';
}

void generate_key(char *text, char *key_phrase, char *key) {
    strcpy(key, key_phrase);
    int text_len = strlen(text);
    int key_len = strlen(key_phrase);
    
    for (int i = 0; i < text_len; i++) {
        if (strlen(key) < text_len) {
            key[i] = key_phrase[i % key_len];
        }
    }
    key[text_len] = '\0';
}

void encrypt(char *text, char *key_phrase) {
    prepare_text(text);
    char key[200];
    generate_key(text, key_phrase, key);
    
    for (int i = 0; text[i]; i++) {
        text[i] = ((text[i] - 'A') + (key[i] - 'A')) % 26 + 'A';
    }
}

void decrypt(char *text, char *key_phrase) {
    prepare_text(text);
    char key[200];
    generate_key(text, key_phrase, key);
    
    for (int i = 0; text[i]; i++) {
        text[i] = ((text[i] - 'A' - (key[i] - 'A') + 26) % 26) + 'A';
    }
}

void print_key(char *text, char *key_phrase) {
    char key[200];
    prepare_text(text);
    generate_key(text, key_phrase, key);
    printf("Generated Key: %s\n", key);
}

int main() {
    char text[200];
    char key_phrase[50];
    
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;
    
    printf("Enter key phrase: ");
    scanf("%s", key_phrase);
    
    printf("\nOriginal: %s\n", text);
    
    // Encrypt
    char encrypted[200];
    strcpy(encrypted, text);
    encrypt(encrypted, key_phrase);
    printf("Encrypted: %s\n", encrypted);
    
    // Show generated key
    print_key(encrypted, key_phrase);
    
    // Decrypt
    char decrypted[200];
    strcpy(decrypted, encrypted);
    decrypt(decrypted, key_phrase);
    printf("Decrypted: %s\n", decrypted);
    
    return 0;
}
