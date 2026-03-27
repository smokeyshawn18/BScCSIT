#include <stdio.h>

/*
============================================================
🧪 EXPERIMENT: Simulation of Static Mathematical Model
============================================================

🎯 OBJECTIVE:
To simulate a static mathematical model using a tax 
calculation system in C programming.

------------------------------------------------------------
📘 THEORETICAL BACKGROUND:

A static mathematical model represents a system using 
equations without involving time.

In finance, tax can be calculated as:

    Tax = Income × Tax Rate

And Net Income:

    Net Income = Income - Tax

This model is static because the output depends only on 
input values and does not depend on time.

------------------------------------------------------------
💻 SOURCE CODE:
(Program written below)

------------------------------------------------------------
📊 RESULTING OUTPUT (Sample):

Income    Tax     Net Income
1000.00   100.00  900.00
1100.00   110.00  990.00
1200.00   120.00  1080.00
...

------------------------------------------------------------
📝 CONCLUSION:

The program successfully simulates a static tax model. 
The output depends only on the income value and tax rate, 
showing a simple static mathematical relationship.

============================================================
*/

int main() {
    float income = 1000;
    float taxRate = 0.10; // 10% tax
    float tax, netIncome;

    printf("Income\tTax\tNet Income\n");

    for(int i = 0; i < 10; i++) {
        tax = income * taxRate;
        netIncome = income - tax;

        printf("%.2f\t%.2f\t%.2f\n", income, tax, netIncome);

        // Increase income
        income += 100;
    }

    return 0;
}