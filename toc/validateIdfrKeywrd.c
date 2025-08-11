#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// List of 32 C keywords
const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};
const int keyword_count = 32;

// Function to check if a string is a keyword
bool isKeyword(const char* str) {
    for (int i = 0; i < keyword_count; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to check if a string is a valid identifier
bool isValidIdentifier(const char* str) {
    int len = strlen(str);
    if (len == 0)
        return false;

    // Check first character
    if (!(isalpha(str[0]) || str[0] == '_'))
        return false;

    // Check remaining characters
    for (int i = 1; i < len; i++) {
        if (!(isalnum(str[i]) || str[i] == '_'))
            return false;
    }

    // Check if keyword
    if (isKeyword(str))
        return false;

    return true;
}

int main() {
    char input[100];
    printf("Enter a string to validate as C identifier: ");
    scanf("%99s", input);

    if (isValidIdentifier(input))
        printf("\"%s\" is a valid identifier.\n", input);
    else if (isKeyword(input))
        printf("\"%s\" is a keyword and cannot be used as identifier.\n", input);
    else
        printf("\"%s\" is not a valid identifier.\n", input);

    return 0;
}
