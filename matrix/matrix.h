#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include"matrix_global.h"

class Matrix : public MatrixGlobal 
{
public:
	Matrix(void);
	Matrix(size_t r, size_t c);
	Matrix(size_t r);
	Matrix(const std::string& filename);
  Matrix(MatrixGlobal mg);
  Matrix(MatrixOperations mo);
  Matrix(MatrixArithmetic ma);
};

Matrix::Matrix(void) : MatrixGlobal(){/*Do Nothing*/}
Matrix::Matrix(size_t r, size_t c) : MatrixGlobal(r, c){/*Do Nothing*/}
Matrix::Matrix(size_t r) : MatrixGlobal(r){/*Do Nothing*/}
Matrix::Matrix(const std::string& filename) : MatrixGlobal(filename){/*Do Nothing*/}

Matrix::Matrix(MatrixGlobal mg) : MatrixGlobal(mg.rows(), mg.columns())
{
  for(size_t r = 0; r < mg.rows(); ++r)
  {
    for(size_t c = 0; c < mg.columns(); ++c)
    {
      this->set_entry(mg.read_entry(r,c), r, c);
    }
  }
}

Matrix::Matrix(MatrixOperations mo) : MatrixGlobal(mo.rows(), mo.columns())
{
  for(size_t r = 0; r < mo.rows(); ++r)
  {
    for(size_t c = 0; c < mo.columns(); ++c)
    {
      this->set_entry(mo.read_entry(r,c), r, c);
    }
  }
}

Matrix::Matrix(MatrixArithmetic ma) : MatrixGlobal(ma.rows(), ma.columns())
{
  for(size_t r = 0; r < ma.rows(); ++r)
  {
    for(size_t c = 0; c < ma.columns(); ++c)
    {
      this->set_entry(ma.read_entry(r,c), r, c);
    }
  }
}

#endif // MATRIX_H_INCLUDED