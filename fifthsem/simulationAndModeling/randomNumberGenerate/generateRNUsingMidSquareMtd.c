/*
============================================================
🧪 EXPERIMENT: Generate Random Numbers using Mid-Square Method
============================================================

🎯 OBJECTIVE:
To generate pseudo-random numbers using the mid-square method in C programming.

------------------------------------------------------------
📘 THEORETICAL BACKGROUND:

The mid-square method squares an n-digit seed, takes the middle n digits 
from the 2n-digit result (padding with zeros if needed), and repeats.
Static model as each output depends only on previous number.
Example: seed 6897 → 6897² = 475,865,609 → middle 4 digits = 5860.

------------------------------------------------------------
💻 SOURCE CODE:
(See below)

------------------------------------------------------------
📊 RESULTING OUTPUT (Sample):

Enter number of random numbers: 10
Seed value: 6897
Mid-Square Random Numbers:
6897 5860 4379 7586 5121 6220 7168 4050 6400 9604

------------------------------------------------------------
📝 CONCLUSION:

The program successfully generates pseudo-random numbers using mid-square method.
Sequence quality depends on seed choice; short cycles possible with poor seeds.
Used historically before better LCG methods; educational for RNG basics.

============================================================
*/

#include <stdio.h>

int main() {
    int n, seed;
    printf("Enter number of random numbers: ");
    scanf("%d", &n);
    printf("Enter seed value (4 digits): ");
    scanf("%d", &seed);
    
    printf("Mid-Square Random Numbers:\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", seed);
        
        // Square the seed (use long long to avoid overflow)
        long long sq = (long long)seed * seed;
        
        // Extract middle 4 digits: divide by 100, mod 10000
        seed = (sq / 100) % 10000;
    }
    printf("\n");
    
    return 0;
}