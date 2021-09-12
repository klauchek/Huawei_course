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

int SolveSquare(const double a, const double b, const double c, double *x1, double *x2)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (Compare(a, 0.0))
    {
        return SolveLinear(b, c, x1);
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

//---------------------------------------------------------------------
//! Solves a linear equation bx + c = 0  
//! @param [in]  b   b‐coefficient 
//! @param [in]  c   c‐coefficient 
//! @param [out] x  Pointer to the 1st root 
//! 
//! @return Number of roots
//!
//! @note   Returns INF_ROOTS if equation has infinity amount of roots
//!                 ZERO_ROOTS if equation has no roots in real numbers
//!                 ONE_ROOT if equation has one root
//----------------------------------------------------------------------

int SolveLinear(const double b, const double c, double *x)
{
    if (Compare(b, 0.0))
    {
        return (Compare(c, 0.0)) ? INF_ROOTS : ZERO_ROOTS;
    }
    else
    {
        *x = -c / b;
        return ONE_ROOT;
    }
}

//---------------------------------------------------------------------
//! Prints roots 
//! @param [in]  number_of_roots   Number of roots 
//! @param [out] x1                Pointer to the 1st root 
//! @param [out] x2                Pointer to the 2nd root
//----------------------------------------------------------------------

void PrintRoots(int number_of_roots, const double x1, const double x2)
{
    switch (number_of_roots) //!TODO PrintRoots
    {
        case ONE_ROOT: 
                printf("x = %lg\n", x1);
                break;
        
        case TWO_ROOTS: 
                printf("x1 = %lg, x2 = %lg\n", x1, x2);\
                break;
        
        case INF_ROOTS: 
                printf("Any number\n");
                break;

        case ZERO_ROOTS:
                printf("No roots\n");
                break;
                
        default: 
                printf ("%s(): ERROR: Incorrect amount of roots: %d\n", __FUNCTION__, number_of_roots);
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

inline bool Compare (const double a, const double b)
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
inline double CalcDiscriminant (const double a, const double b, const double c)
{
    return b * b - 4 * a * c;
}

//---------------------------------------------------------------------
//! Tests SolveSquare function 
//! @param [in]  a   a‐coefficient 
//! @param [in]  b   b‐coefficient 
//! @param [in]  c   c‐coefficient 
//! @param [out] x1  1st expected root
//! @param [out] x2  2nd expected root
//! 
//! @return 1 if test passed
//!         0 if test failed
//----------------------------------------------------------------------

int UnitTest(const double a, const double b, const double c, const double x1, const double x2, int correct_number_of_roots, int test_number)
{
  double root1 = NAN, root2 = NAN;
  int number_of_roots = SolveSquare(a, b, c, &root1, &root2);
  if (number_of_roots == correct_number_of_roots)
  {
      switch (number_of_roots)
      {
        case ZERO_ROOTS:
                return 1;
        
        case INF_ROOTS:
                return 1;
        
        case ONE_ROOT:
            if (Compare(root1, x1))
                return 1;
        case TWO_ROOTS:
            if ((Compare(root1, x1) && Compare(root2, x2)) || (Compare(root1, x2) && Compare(root2, x1)))
                return 1;

        default: return 0;
      }
  }
  else
  {
    printf("Test number %d failed\n"
    "x1 = %f, x2 = %f, %d roots\n"
    "Expected result: x1 = %f, x2 = %f, %d roots\n",
    test_number, root1, root2, number_of_roots, x1, x2, correct_number_of_roots);

    return 0;
  }
}


//------------------------------------------
//! Runs UnitTests for SolveSquare function
//------------------------------------------
int TestSolveSquare(void)
{
  UnitTest(1, 1, 1, NAN, NAN, ZERO_ROOTS, 1);

  UnitTest(1, 3, -4, -4, 1, TWO_ROOTS, 2);

  UnitTest(1, 0, 0, 0, NAN, ONE_ROOT, 3);

  UnitTest(2.4, -6.9, 4.8, 1.17981, 1.69519, TWO_ROOTS, 4);

  UnitTest(0, 0, 13, NAN, NAN, ZERO_ROOTS, 5);

  UnitTest(0, 0, 0, NAN, NAN, INF_ROOTS, 6);

  UnitTest(0, 0.0000003, 7, -7 / 0.0000003, NAN, ONE_ROOT, 7);

  UnitTest(1, 0, -5, sqrt(5), -sqrt(5), TWO_ROOTS, 8);

  return 1;
}

/////////////////////////
void CheckInput(int roots)
{
    if (roots != 3)
        printf("Incorrect input\n");
}
