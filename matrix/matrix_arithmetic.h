#ifndef MATRIX_ARITHMETIC_H_INCLUDED
#define MATRIX_ARITHMETIC_H_INCLUDED

#include"matrix_base.h"

class MatrixArithmetic : public MatrixBase 
{
public:
  MatrixArithmetic(void);
  MatrixArithmetic(size_t r, size_t c);
  MatrixArithmetic(size_t r);
  MatrixArithmetic(const std::string& filename);
  MatrixArithmetic multiply(MatrixArithmetic other);
  MatrixArithmetic operator*(MatrixArithmetic& other);
  MatrixArithmetic add(MatrixArithmetic other);
  MatrixArithmetic operator+(MatrixArithmetic& other);
  MatrixArithmetic scalar_multiply(int scalar);
};

MatrixArithmetic::MatrixArithmetic(void) : MatrixBase(){/*Do nothing*/}
MatrixArithmetic::MatrixArithmetic(size_t r, size_t c) : MatrixBase(r, c){/*Do nothing*/}
MatrixArithmetic::MatrixArithmetic(size_t r) : MatrixBase(r){/*Do nothing*/}
MatrixArithmetic::MatrixArithmetic(const std::string& filename) : MatrixBase(filename){/*Do nothing*/}

MatrixArithmetic MatrixArithmetic::multiply(MatrixArithmetic other)
{
    MatrixArithmetic out(this->rows(), other.columns());
    if (this->columns() != other.rows())
    {
        throw "Columns of left must equal rows of right";
    }
    for(size_t r = 0; r < out.rows(); r++)
    {
        for(size_t c = 0; c < out.columns(); c++)
        {
            out.set_entry(dot_product(copy_row(r), other.copy_column(c)), r,c);
        }
    }
    return out;
}

MatrixArithmetic MatrixArithmetic::operator*(MatrixArithmetic& other)
{
    MatrixArithmetic out = this->multiply(other);
    return out;
}

MatrixArithmetic MatrixArithmetic::add(MatrixArithmetic other)
{
    if((this->rows() != other.rows()) || (this->columns() != other.columns())){
        throw "Dimensions must be equal";
    }
    MatrixArithmetic out(this->rows(), this->columns());
    for(size_t r = 0; r < this->rows(); ++r)
    {
        for(size_t c = 0; c < this->columns(); ++c)
        {
            out.set_entry(this->read_entry(r,c) + other.read_entry(r,c), r, c );
        }
    }
    return out;
}

MatrixArithmetic MatrixArithmetic::operator+(MatrixArithmetic& other)
		{
			MatrixArithmetic out = this->add(other);
			return out;
		}

MatrixArithmetic MatrixArithmetic::scalar_multiply(int scalar)
{
    MatrixArithmetic out(this->rows(), this->columns());
    for(size_t r = 0; r < out.rows(); ++r)
    {
        for(size_t c = 0; c < out.columns(); ++c)
        {
            out.set_entry(scalar * this->read_entry(r, c), r, c);
        }
    }
    return out;
}

#endif