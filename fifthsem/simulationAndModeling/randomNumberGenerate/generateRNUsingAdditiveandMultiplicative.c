/*
============================================================
🧪 EXPERIMENT: Generate Random Numbers using Additive and Multiplicative Congruential Methods
============================================================

🎯 OBJECTIVE:
To generate pseudo-random numbers using additive congruential method (Xn = (X_{n-1} + c) mod m)
and multiplicative congruential method (Xn = (a * X_{n-1}) mod m) in C programming.

------------------------------------------------------------
📘 THEORETICAL BACKGROUND:

These are Linear Congruential Generators (LCG) for pseudo-random number simulation.
- Additive: Includes increment c ≠ 0.
- Multiplicative: Sets c=0, uses multiplier a.
Static as outputs depend only on seed, parameters, no time evolution beyond iterations.
Parameters: seed X0=3, modulus m=15, c=2 (additive), a=7 (multiplicative), 10 numbers.

------------------------------------------------------------
💻 SOURCE CODE:
(See below)

------------------------------------------------------------
📊 RESULTING OUTPUT (Sample):

Additive Congruential Random Numbers:
3 5 7 9 11 13 0 2 4 6

Multiplicative Congruential Random Numbers:
3 6 12 9 3 6 12 9 3 6

------------------------------------------------------------
📝 CONCLUSION:

The program successfully generates pseudo-random sequences using both methods.
Additive produces a longer cycle; multiplicative cycles quickly (period 4 here).
These simulate randomness for static Monte Carlo models without stdlib rand().

============================================================
*/

#include <stdio.h>

int main() {
    int X0 = 3, m = 15, c = 2, a = 7, n = 10;
    
    // Additive Congruential
    printf("Additive Congruential Random Numbers:\n");
    int X_add = X0;
    printf("%d ", X_add);
    for(int i = 1; i < n; i++) {
        X_add = (X_add + c) % m;
        printf("%d ", X_add);
    }
    printf("\n\n");
    
    // Multiplicative Congruential
    printf("Multiplicative Congruential Random Numbers:\n");
    int X_mul = X0;
    printf("%d ", X_mul);
    for(int i = 1; i < n; i++) {
        X_mul = (a * X_mul) % m;
        printf("%d ", X_mul);
    }
    printf("\n");
    
    return 0;
}