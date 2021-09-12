#ifndef SQUARE_EQ
#define SQUARE_EQ

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

const double EPSILON = 1e-9;

enum Roots
{
    INF_ROOTS = -1,
    ZERO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2
};
//!TODO consts everywhere or no.
int SolveSquare(const double a, const double b, const double c, double *x1, double *x2);
int SolveLinear(const double b, const double c, double *x);
int TestSolveSquare(void);
int UnitTest(double a, double b, double c, double x1, double x2, int number_of_roots, int test_number);
void CheckInput(int roots);
void PrintRoots(int number_of_roots, const double x1, const double x2);
inline bool Compare (const double a, const double b);
inline double CalcDiscriminant (const double a, const double b, const double c);


#endif // SQUARE_EQ