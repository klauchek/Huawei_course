#include "square_eq.h"


int main(void)
{

        printf("Square equation solver \n");
        printf("Enter the coefficients a, b, c:\n");


        double a = NAN, b = NAN, c = NAN;
        scanf("%lg %lg %lg", &a, &b, &c); //!TODO check scanf return
        //if (scnaf != 3) ??

        double x1 = NAN, x2 = NAN;
        int number_of_roots = SolveSquare (a, b, c, &x1, &x2);

        PrintRoots(number_of_roots, x1, x2);

        return 0;
}

