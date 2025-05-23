#include <stdio.h>
#include <string.h>

void printPrefixes(char str[]) {
    int len = strlen(str);
    printf("\nPrefixes:\n");
    for (int i = 1; i <= len; i++) {
        for (int j = 0; j < i; j++) {
            printf("%c", str[j]);
        }
        printf("\n");
    }
}

void printSuffixes(char str[]) {
    int len = strlen(str);
    printf("\nSuffixes:\n");
    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            printf("%c", str[j]);
        }
        printf("\n");
    }
}

void printSubstrings(char str[]) {
    int len = strlen(str);
    printf("\nSubstrings:\n");
    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            for (int k = i; k <= j; k++) {
                printf("%c", str[k]);
            }
            printf("\n");
        }
    }
}

int main() {
    char str[100];

    printf("Enter a string: ");
    scanf("%s", str); 

    printPrefixes(str);
    printSuffixes(str);
    printSubstrings(str);

    return 0;
}
