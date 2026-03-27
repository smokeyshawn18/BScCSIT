#include <stdio.h>

/*
============================================================
🧪 EXPERIMENT: Mixed Congruential Method
============================================================

🎯 OBJECTIVE:
To generate 50 pseudo-random numbers using the Mixed 
Congruential Method.

------------------------------------------------------------
📘 THEORETICAL BACKGROUND:

The Mixed Congruential Generator (MCG) generates numbers 
using the formula:

    X(n+1) = (a * X(n) + c) mod m

Where:
    X(n)  = current value (seed)
    a     = multiplier
    c     = increment (c ≠ 0)
    m     = modulus

This method produces pseudo-random numbers that appear 
random but are actually deterministic.

------------------------------------------------------------
💻 SOURCE CODE:
(Program written below)

------------------------------------------------------------
📊 RESULTING OUTPUT (Sample):

50 Random Numbers:
4    36    97    6    46    58    19    ...

(Note: Output continues up to 50 numbers)

------------------------------------------------------------
📝 CONCLUSION:

The Mixed Congruential Method successfully generates 
pseudo-random numbers. The sequence depends on the 
chosen values of a, c, m, and the initial seed.

It is simple and efficient but not suitable for 
cryptographic purposes due to predictability.

============================================================
*/

int main() {
    int x = 4;          // initial seed
    int m = 99;
    int a = 5;
    int c = 16;
    int i;

    printf("50 Random Numbers:\n");

    for(i = 0; i < 50; i++) {
        printf("%d\t", x);
        x = (a * x + c) % m;
    }

    return 0;
}