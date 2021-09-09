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

int SolveSquare(double a, double b, double c, double *x1, double *x2);
//bool CheckInput (??);
inline bool Compare (double a, double b);//проверять равенство между собой и с нулем
inline double CalcDiscriminant (double a, double b, double c);//может оказаться отрицательным и прочая хуйня


#endif // SQUARE_EQ