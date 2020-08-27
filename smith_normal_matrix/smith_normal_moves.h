#ifndef SMITH_NORMAL_MOVES_H_INCLUDED
#define SMITH_NORMAL_MOVES_H_INCLUDED

#include"smith_normal_tests.h"
#include"smith_normal_auxiliaries.h"
#include"../bezout/bezout.h"
#include <string>
#include <bits/stdc++.h>

class SmithNormalMoves : public SmithNormalTests
{
public:
  SmithNormalMoves(void);
	SmithNormalMoves(size_t r, size_t c);
	SmithNormalMoves(size_t r);
	SmithNormalMoves(const std::string& filename);
  SmithNormalMoves(SmithNormalTests mat);
  std::stack <Matrix> row_ops;
  std::stack <Matrix> column_ops;
  void improve_pivot_down(size_t i);
  void improve_pivot_right(size_t i);
  void refine_row(size_t r1, size_t r2);
  void refine_column(size_t c1, size_t c2);
  void pivot_into_place(size_t r, size_t c, size_t t);
};

SmithNormalMoves::SmithNormalMoves(void) : SmithNormalTests(){/* Do Nothing*/}
SmithNormalMoves::SmithNormalMoves(size_t r, size_t c) : SmithNormalTests(r, c){/* Do Nothing*/}
SmithNormalMoves::SmithNormalMoves(size_t r) : SmithNormalTests(r){/* Do Nothing*/}
SmithNormalMoves::SmithNormalMoves(const std::string& filename) : SmithNormalTests(filename){/* Do Nothing*/}
SmithNormalMoves::SmithNormalMoves(SmithNormalTests mat) : 
SmithNormalTests(mat.rows(), mat.columns())
{
  for(size_t r = 0; r < mat.rows(); ++r)
  {
    for(size_t c = 0; c < mat.columns(); ++c)
    {
      this->set_entry(mat.read_entry(r,c), r, c);
    }
  }
}

void SmithNormalMoves::improve_pivot_down(size_t i)
{
    if (!(i < this->rows()))
    {
        throw "improve pivot down: Row index out of range!";
    }
    if (this->read_entry(i,i) ==0 )
    {
        throw "improve pivot down: Cannot pivot on a zero entry!";
    }
    if (i + 1 < this->rows())
    {
        for(size_t j = i + 1; j< this->rows(); j++)
        {
            if (this->read_entry(j,i) == 0) continue;
            this->refine_row(i,j);
        }
    }

}
void SmithNormalMoves::improve_pivot_right(size_t i)
{
    if (!(i < this->columns()))
    {
        throw "improve pivot right: Column index out of range!";
    }
    if (this->read_entry(i,i) ==0 )
    {
        throw "improve pivot right: Cannot pivot on a zero entry!";
    }
    if (i + 1 < this->columns() )
    {
        for(size_t j = i + 1; j < this->columns(); j++)
        {
            if (this->read_entry(i,j) == 0) continue;

            this->refine_column(i, j);
        }
    }
}

void SmithNormalMoves::refine_row(size_t r1, size_t r2)
{
    Bezout data(this->read_entry(r1, r1), this->read_entry(r2, r1));
    RRMatrix rr(this->rows(), r1, r2, data);
    this->combine_rows(r1 , r2, data.s, data.t, -data.target / data.gcd, data.pivot / data.gcd );
    this->row_ops.push(rr);
}

void SmithNormalMoves::refine_column(size_t c1, size_t c2)
{
    Bezout data(this->read_entry(c1, c1), this->read_entry(c1, c2));
    CRMatrix cr(this->columns(), c1, c2, data );
    this->combine_columns(c1 , c2, data.s, data.t, - data.target / data.gcd, data.pivot / data.gcd );
    this->column_ops.push(cr);
}

void SmithNormalMoves::pivot_into_place(size_t r, size_t c, size_t t)
{
        RSMatrix rsm(this->rows(), r, t);
        CSMatrix csm(this->columns(), c, t);
        this->swap_rows(r, t);
        this->swap_columns(c, t);
        this->row_ops.push(rsm);
        this->column_ops.push(csm);
}
#endif