#ifndef SMITH_NORMAL_TESTS_H_INCLUDED
#define SMITH_NORMAL_TESTS_H_INCLUDED

#include"../matrix/matrix.h"

struct Index
{
	size_t row;
	size_t column;
	bool pivot_found = false;
};

class SmithNormalTests : public Matrix 
{
public:
  SmithNormalTests(void);
	SmithNormalTests(size_t r, size_t c);
	SmithNormalTests(size_t r);
	SmithNormalTests(const std::string& filename);
  SmithNormalTests(Matrix mat);
  Index find_pivot(size_t index);
  bool pivot_zeroed(size_t pivot);
  bool zeroes_below_pivot(size_t pivot);
  bool zeroes_rightof_pivot(size_t pivot);
};

SmithNormalTests::SmithNormalTests(void) : Matrix(){/* Do Nothing*/}
SmithNormalTests::SmithNormalTests(size_t r, size_t c) : Matrix(r,c){/* Do Nothing*/}
SmithNormalTests::SmithNormalTests(size_t r) : Matrix(r){/* Do Nothing*/} 
SmithNormalTests::SmithNormalTests(const std::string& filename) : Matrix(filename){/* Do Nothing*/} 
SmithNormalTests::SmithNormalTests(Matrix mat) : Matrix(mat.rows(), mat.columns())
{
  for(size_t r = 0; r < mat.rows(); ++r)
  {
    for(size_t c = 0; c < mat.columns(); ++c)
    {
      this->set_entry(mat.read_entry(r,c), r, c);
    }
  }
}

Index SmithNormalTests::find_pivot(size_t index)
{
    /* We are looking for a nonzero entry at or "below" (index, index)*/
    Index out;
    out.row = index;
    out.column = index;
    out.pivot_found = false;
    if (!(out.row < this->rows()) || !(out.column < this->columns()))
    {
        return out;
    }
    int entry = this->read_entry(out.row, out.column);
    if(entry != 0)
    {
        out.pivot_found = true;
        return out;
    }

    while(entry == 0 && (out.column < this->columns()))
    {
        /* Look down column out.column for a non-zero entry*/
        while(entry == 0 && (out.row < this->rows()))
        {
            out.row += 1;
            if (out.row < this->rows())
            {
                /*When a non-zero entry is found we are done*/
                if (!(out.row < this->rows()) || !(out.column < this->columns()))
                {
                    return out;
                }
                entry = this->read_entry(out.row, out.column);
                if ( entry!= 0)
                {
                    out.pivot_found = true;
                    return out;
                }
            }
        }
        /* Having not found a nonzero entry in this column, move to the next column and start over*/
        out.row = index;
        out.column += 1;
        if (out.column < this->columns())
        {
            entry = this->read_entry(out.row, out.column);
            if ( entry!=0)
            {
                out.pivot_found = true;
                return out;
            }
        }
    }
    /* If no pivot was found say so*/
    out.row = 0;
    out.column = 0;
    out.pivot_found = false;
    return out;
}


bool SmithNormalTests::pivot_zeroed(size_t pivot)
{
    return this->zeroes_below_pivot(pivot) && this->zeroes_rightof_pivot(pivot);
}

bool SmithNormalTests::zeroes_below_pivot(size_t pivot)
{
    if (pivot >= this->rows()) throw "Index out of bounds";
    if (pivot == this->rows() - 1) return true;
    for(size_t r = pivot + 1; r < this->rows(); r++)
    {
        if (this->read_entry(r, pivot) != 0) return false;
    }
    return true;
}

bool SmithNormalTests::zeroes_rightof_pivot(size_t pivot)
{
    if (pivot >= this->columns()) throw "Index out of bounds";
    if (pivot == this->columns() - 1) return true;
    for(size_t c = pivot + 1; c < this->columns(); c++)
    {
        if (this->read_entry(pivot, c) != 0) return false;
    }
    return true;
}

#endif