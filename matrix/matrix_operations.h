#ifndef MATRIX_OPERATIONS_H_INCLUDED
#define MATRIX_OPERATIONS_H_INCLUDED

#include"matrix_arithmetic.h"

class MatrixOperations : public MatrixArithmetic 
{
public:
  MatrixOperations(void);
  MatrixOperations(size_t r, size_t c);
  MatrixOperations(size_t r);
  MatrixOperations(const std::string& filename);
  MatrixOperations(MatrixArithmetic ma);
  void add_row_multiple(int scalar, size_t r1, size_t r2);
  void swap_rows(size_t r1, size_t r2);
  void combine_rows(size_t r1, size_t r2, int a, int b, int c, int d);
  void add_column_multiple(int scalar, size_t c1, size_t c2);
  void swap_columns(size_t c1, size_t c2);
  void combine_columns(size_t c1, size_t c2, int a, int b, int c, int d);
};

MatrixOperations::MatrixOperations(void) : MatrixArithmetic(){/*Do nothing*/}
MatrixOperations::MatrixOperations(size_t r, size_t c) : MatrixArithmetic(r, c){/*Do nothing*/}
MatrixOperations::MatrixOperations(size_t r) : MatrixArithmetic(r){/*Do nothing*/}
MatrixOperations::MatrixOperations(const std::string& filename) : MatrixArithmetic(filename){/*Do nothing*/}

MatrixOperations::MatrixOperations(MatrixArithmetic ma) : MatrixArithmetic(ma.rows(), ma.columns())
{
  for(size_t r = 0; r < ma.rows(); ++r)
  {
    for(size_t c = 0; c < ma.columns(); ++c)
    {
      this->set_entry(ma.read_entry(r,c), r, c);
    }
  }
}

void MatrixOperations::add_row_multiple(int scalar, size_t r1, size_t r2)
{
 for(size_t c = 0; c < this->columns(); ++c)
  {
		this->set_entry(scalar * this->read_entry(r1,c) + this->read_entry(r2, c), r2, c);
	}
}

void MatrixOperations::swap_rows(size_t r1, size_t r2)
{
    if( !(r1 < this->rows()) || !(r2 < this->rows()) ) throw "swap rows: row size out of bounds!";
    for(size_t c = 0; c < this->columns(); c++)
    {
        int v1 = this->read_entry(r1, c);
        int v2 = this->read_entry(r2, c);
        this->set_entry(v2, r1, c);
        this->set_entry(v1, r2, c);
    }
}

void MatrixOperations::combine_rows(size_t r1, size_t r2, int a, int b, int c, int d)
{
    for(size_t i = 0; i < this->columns(); i++ )
    {
        int e1 = a * this->read_entry(r1, i) + b * this->read_entry(r2,i);
        int e2 = c * this->read_entry(r1, i) + d * this->read_entry(r2,i);
        this->set_entry(e1, r1, i);
        this->set_entry(e2, r2, i);
    }
}

void MatrixOperations::add_column_multiple(int scalar, size_t c1, size_t c2)
{
    for(size_t r = 0; r < this->rows(); r++)
    {
        this->set_entry(scalar * this->read_entry(r,c1) + this->read_entry(r, c2),  r, c2);
    }
}

void MatrixOperations::swap_columns(size_t c1, size_t c2)
{
    if( !(c1 < this->columns()) || !(c2 < this->columns()) ) throw "swap columns: column size out of bounds!";
    for(size_t r = 0; r < this->rows(); r++)
    {
        int v1 = this->read_entry(r, c1);
        int v2 = this->read_entry(r, c2);
        this->set_entry(v2, r, c1);
        this->set_entry(v1, r, c2 );
    }
}

void MatrixOperations::combine_columns(size_t c1, size_t c2, int a, int b, int c, int d)
{
    for(size_t i = 0; i < this->columns(); i++ )
    {
        int e1 = a * this->read_entry(i, c1) + b * this->read_entry(i,c2);
        int e2 = c * this->read_entry(i, c1) + d * this->read_entry(i,c2);
        this->set_entry(e1, i, c1);
        this->set_entry(e2, i, c2);
    }
}
#endif //MATRIX_OPERATIONS_H_INCLUDED