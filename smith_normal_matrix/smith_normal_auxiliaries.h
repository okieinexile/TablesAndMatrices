#ifndef SMITH_NORMAL_AUXILARIIES_H_INCLUDED
#define SMITH_NORMAL_AUXILARIIES_H_INCLUDED

#include"../matrix/matrix.h"
#include"../bezout/bezout.h"

class RRMatrix: public Matrix
{
public:
    RRMatrix(int dimension, int r1, int r2, Bezout bez) : Matrix(dimension)
    {
        this->combine_rows(r1, r2, bez.s, bez.t, - bez.target / bez.gcd, bez.pivot / bez.gcd);
    }
};

class CRMatrix: public Matrix
{
public:
    CRMatrix(int dimension, int c1, int c2, Bezout bez) : Matrix(dimension)
    {
        this->combine_columns(c1, c2, bez.s, bez.t, - bez.target / bez.gcd, bez.pivot / bez.gcd);
    }
};

class RSMatrix: public Matrix
{
public:
    RSMatrix(int dimension, int r1, int r2) : Matrix(dimension)
    {
        this->swap_rows(r1,r2);
    }
};

class CSMatrix: public Matrix
{
public:
    CSMatrix(int dimension, int c1, int c2) : Matrix(dimension)
    {
        this->swap_columns(c1,c2);
    }
};


#endif //SMITH_NORMAL_AUXILARIIES_H_INCLUDED