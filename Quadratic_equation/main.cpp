#include "square_eq.h"


int main(void)
{
        if (TestSolveSquare())
                printf("Unit Tests completed successfully.\n\n");
        else
                printf("Unit Tests failed.\n\n");

        printf("Square equation solver \n");
        printf("Enter the coefficients a, b, c:\n");


        double a = NAN, b = NAN, c = NAN;

        int roots = scanf("%lg %lg %lg", &a, &b, &c);
        CheckInput(roots);

        double x1 = NAN, x2 = NAN;
        int number_of_roots = SolveSquare (a, b, c, &x1, &x2);

        PrintRoots(number_of_roots, x1, x2);

        return 0;
}

