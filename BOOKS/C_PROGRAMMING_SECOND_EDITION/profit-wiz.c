#include <stdlib.h>
#include <stdio.h>

int main(void) {
    float f_TotalRevenue = 0.0;
    float f_TotalCost = 0.0;
    float f_Profit = 0.0;

    printf("\n\n~ Profit Wiz | sun \\t dev ~");

    printf("\nEnter total revenue: ");
    scanf("%f", &f_TotalRevenue);
    printf("\nEnter total cost: ");
    scanf("%f", &f_TotalCost);

    f_Profit = f_TotalRevenue - f_TotalCost;

    if (f_Profit < 0.0) {
        printf("\nCost higher than revenue, you're broke!");
        return EXIT_SUCCESS;
    }

    printf("\nProfit: %.2f", f_Profit);

    return EXIT_SUCCESS;
}