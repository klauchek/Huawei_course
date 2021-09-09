#include "square_eq.h"


int main(void)
{

printf("Square equation solver \n");
printf("Enter the coefficients a, b, c:\n");


double a = 0, b = 0, c = 0;
scanf("%lg %lg %lg", &a, &b, &c);

double x1 = 0, x2 = 0;
int nRoots = SolveSquare (a, b, c, &x1, &x2);

switch (nRoots)
{
        case ZERO_ROOTS: printf("No roots\n");
                break;
            
        case ONE_ROOT: printf("x = %lg\n", x1);
                break;
            
        case TWO_ROOTS: printf("x1 = %lg, x2 = %lg\n", x1, x2);\
                break;
            
        case INF_ROOTS: printf("Any number\n");
                break;
                
        default: printf ("main(): ERROR: Incorrect amount of roots: %d\n", nRoots);
                return 1;
}


return 0;
}

