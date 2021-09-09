#include "square_eq.h"

//---------------------------------------------------------------------
//! Solves a square equation ax^2 + bx + c = 0  
//! @param [in]  a   a‐coefficient 
//! @param [in]  b   b‐coefficient 
//! @param [in]  c   c‐coefficient 
//! @param [out] x1  Pointer to the 1st root 
//! @param [out] x2  Pointer to the 2nd root
//! 
//! @return Number of roots
//!
//! @note   Returns INF_ROOTS if equation has infinity amount of roots
//!                 ZERO_ROOTS if equation has no roots in real numbers
//!                 ONE_ROOT if equation has one root
//!                 TWO_ROOTS if equation has two roots
//----------------------------------------------------------------------

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


//------------------------------------------
//! Compares two numbers
//! @param [in] a   first number
//! @param [in] b   second number
//!
//! @return Returns 1 if numbers are equal
//!                 0 otherwise
//!
//! @note   Accuracy is defined by EPSILON constant
//------------------------------------------

inline bool Compare (double a, double b)
{
    return (fabs(a - b) < EPSILON);
}

//------------------------------------------
//! Calculates discriminant
//! @param [in]  a   a‐coefficient 
//! @param [in]  b   b‐coefficient 
//! @param [in]  c   c‐coefficient 
//!
//! @return discriminant
//------------------------------------------
inline double CalcDiscriminant (double a, double b, double c)
{
    return b * b - 4 * a * c;
}



//bool CheckInput (??)