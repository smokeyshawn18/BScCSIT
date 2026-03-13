#include <stdio.h>
#include <stdlib.h>

// Iterative Euclidean Algorithm for GCD
int euclidean_gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Iterative Extended Euclidean Algorithm
// Returns GCD and sets x, y such that a*x + b*y = gcd
int extended_euclidean(int a, int b, int *x, int *y) {
    int x1 = 0, y1 = 1, x2 = 1, y2 = 0;
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    while (b != 0) {
        int q = a / b;
        int temp = b;
        b = a % b;
        a = temp;
        
        temp = x1;
        x1 = x2 - q * x1;
        x2 = temp;
        
        temp = y1;
        y1 = y2 - q * y1;
        y2 = temp;
    }
    *x = x2;
    *y = y2;
    return a;
}

int main() {
    int choice, a, b, g, x, y;
    
    printf("=== Euclidean and Extended Euclidean Algorithms ===\n");
    printf("1. Basic Euclidean Algorithm (GCD)\n");
    printf("2. Extended Euclidean Algorithm (GCD + Coefficients)\n");
    printf("3. Exit\n");
    printf("Choose option: ");
    
    while (scanf("%d", &choice) == 1) {
        if (choice == 3) {
            printf("Exiting...\n");
            break;
        }
        
        if (choice != 1 && choice != 2) {
            printf("Invalid choice! Enter 1, 2, or 3: ");
            continue;
        }
        
        printf("Enter two positive integers a and b: ");
        if (scanf("%d %d", &a, &b) != 2 || a <= 0 || b <= 0) {
            printf("Please enter valid positive integers!\n");
            continue;
        }
        
        if (choice == 1) {
            g = euclidean_gcd(a, b);
            printf("GCD(%d, %d) = %d\n\n", a, b, g);
        } else {
            g = extended_euclidean(a, b, &x, &y);
            printf("GCD(%d, %d) = %d\n", a, b, g);
            printf("%d * %d + %d * %d = %d\n\n", a, x, b, y, g);
        }
        
        printf("Choose option (1/2/3): ");
    }
    
    return 0;
}
