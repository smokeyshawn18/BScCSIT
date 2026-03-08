#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generate_keymap(char *key_phrase, char keymap[26]) {  // Fixed: char *key_phrase
    int used[26] = {0};
    int idx = 0;
    
    // Place key phrase letters first (unique, lowercase)
    for (int i = 0; key_phrase[i] != '\0' && idx < 26; i++) {
        int pos = tolower(key_phrase[i]) - 'a';
        if (pos >= 0 && pos < 26 && !used[pos]) {
            keymap[idx++] = 'a' + pos;
            used[pos] = 1;
        }
    }
    
    // Fill remaining with unused letters
    for (int i = 0; i < 26 && idx < 26; i++) {
        if (!used[i]) {
            keymap[idx++] = 'a' + i;
        }
    }
}

void encrypt(char text[], char keymap[26]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = keymap[text[i] - 'A'] - 'a' + 'A';
        }
        else if (islower(text[i])) {
            text[i] = keymap[text[i] - 'a'];
        }
    }
}

void decrypt(char text[], char keymap[26]) {
    // Create inverse mapping for decryption
    char inv_keymap[26];
    for (int i = 0; i < 26; i++) {
        inv_keymap[keymap[i] - 'a'] = i + 'a';
    }
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = inv_keymap[text[i] - 'A'] - 'a' + 'A';
        }
        else if (islower(text[i])) {
            text[i] = inv_keymap[text[i] - 'a'];
        }
    }
}

int main() {
    char text[100];
    char keymap[26];
    char key_phrase[50];  // Fixed: proper name

    printf("Enter a word: ");
    scanf("%s", text);

    printf("Enter key phrase: ");
    scanf("%s", key_phrase);

    generate_keymap(key_phrase, keymap);  // Fixed: passes char*
    
    // Show the key mapping
    printf("Key mapping: abcdefghijklmnopqrstuvwxyz -> ");
    for (int i = 0; i < 26; i++) {
        printf("%c", keymap[i]);
    }
    printf("\n");

    // Make copy for encryption demo
    char encrypted[100];
    strcpy(encrypted, text);
    encrypt(encrypted, keymap);
    printf("Encrypted text: %s\n", encrypted);

    // Decrypt back to original
    decrypt(encrypted, keymap);
    printf("Decrypted text: %s\n", encrypted);

    return 0;
}
