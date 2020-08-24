#ifndef MATRIX_GLOBAL_H_INCLUDED
#define MATRIX_GLOBAL_H_INCLUDED

#include"matrix_operations.h"

class MatrixGlobal : public MatrixOperations 
{
public:
  MatrixGlobal(void);
	MatrixGlobal(size_t r, size_t c);
	MatrixGlobal(size_t r);
	MatrixGlobal(const std::string& filename);
  MatrixGlobal(MatrixOperations mo);
  MatrixGlobal copy(void);
  MatrixGlobal transpose(void);
  MatrixGlobal left_identity(void);
  MatrixGlobal right_identity(void);
};

MatrixGlobal::MatrixGlobal(void) : MatrixOperations(){/*Do Nothing*/}
MatrixGlobal::MatrixGlobal(size_t r, size_t c) : MatrixOperations(r, c){/*Do Nothing*/}
MatrixGlobal::MatrixGlobal(size_t r) : MatrixOperations(r){/*Do Nothing*/}
MatrixGlobal::MatrixGlobal(const std::string& filename) : MatrixOperations(filename){/*Do Nothing*/}

MatrixGlobal::MatrixGlobal(MatrixOperations mo) : MatrixOperations(mo.rows(), mo.columns())
{
  for(size_t r = 0; r < mo.rows(); ++r)
  {
    for(size_t c = 0; c < mo.columns(); ++c)
    {
      this->set_entry(mo.read_entry(r,c), r, c);
    }
  }
}

MatrixGlobal MatrixGlobal::copy(void)
{
  MatrixGlobal out(this->rows(), this->columns());
  for(size_t r = 0; r < this->rows(); ++r)
  {
    for(size_t c = 0; c < this->columns(); ++c)
    {
      out.set_entry(this->read_entry(r,c), r, c);
    }
  }
  return out;
}

MatrixGlobal MatrixGlobal::transpose(void)
{
  MatrixGlobal out(this->columns(), this->rows());
   for(size_t r = 0; r < out.rows(); r++)
   {
      for(size_t c = 0; c < out.columns(); c++)
      {
        out.set_entry(this->read_entry(c,r), r, c);
      }
   }
   return out;
}

MatrixGlobal MatrixGlobal::left_identity(void)
{
    MatrixGlobal out(this->rows(), this->rows());
    for(size_t i = 0; i < this->rows(); ++i)
    {
        out.set_entry(1, i, i);
    }
    return out;
}

MatrixGlobal MatrixGlobal::right_identity(void)
{
    MatrixGlobal out(this->columns(), this->columns());
    for(size_t i = 0; i < this->columns(); ++i)
    {
        out.set_entry(1, i, i);
    }
    return out;
}

#endif