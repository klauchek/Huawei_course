#include "square_eq.h"

int SolveSquare(double a, double b, double c, double *x1, double *x2)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert( x1 != NULL);
    assert( x2 != NULL);
    assert( x1 != x2);

    if (Compare(a, 0.0))
    {
        if (Compare(b, 0.0))
        {
            return (Compare(c, 0.0)) ? INF_ROOTS : ZERO_ROOTS;
        }
        else
        {
            *x1 = -c / b;
            return ONE_ROOT;
        }
    }
    else
    {
        double d = CalcDiscriminant(a, b, c);

        if (Compare(d, 0.0))
        {
            *x1 = *x2 = -b / (2 * a);
            return ONE_ROOT;
        }
        else if (d > 0)
        {
            double sqrt_d = sqrt(d);

            *x1 = (-b - sqrt_d) / (2 * a);
            *x2 = (-b + sqrt_d) / (2 * a);

            return TWO_ROOTS;
        }

        else 
            return ZERO_ROOTS;
    }

}

inline bool Compare (double a, double b)
{
    return (fabs(a - b) < EPSILON);
}

inline double CalcDiscriminant (double a, double b, double c)
{
    return b * b - 4 * a * c;
}

//bool CheckInput (??)