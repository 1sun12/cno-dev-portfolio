#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int i_Operand1 = 0;
    int i_Operand2 = 0;
    int i_Result = 0;

    printf("\n\nAdder Program - sun\n\n");
    printf("\nEnter first operand: ");
    scanf("%d", &i_Operand1);
    printf("\nEnter second operand: ");
    scanf("%d", &i_Operand2);
    
    i_Result = i_Operand1 + i_Operand2;

    printf("\nThe Result: %d", i_Result);

    return EXIT_SUCCESS;
}