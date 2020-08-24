#ifndef MATRIX_BASE_H_INCLUDED
#define MATRIX_BASE_H_INCLUDED

#include"../integer_table/integer_table.h"

class MatrixBase : public IntegerTable 
{
public:
  MatrixBase(void);
  MatrixBase(size_t r, size_t c);
  MatrixBase(size_t r);
  MatrixBase(const std::string& filename);
  std::vector<int> vector_product(std::vector<int> v, std::vector<int> w); 
  int dot_product(std::vector<int> v, std::vector<int> w);
  int sum(std::vector<int> v);
};

MatrixBase::MatrixBase(void) : IntegerTable(){/* Do nothing */}

MatrixBase::MatrixBase(size_t r, size_t c): IntegerTable(r, c){/* Do nothing */}

MatrixBase::MatrixBase(size_t r) : IntegerTable(r, r)
{
    for(size_t i = 0; i < r; ++i) this->set_entry(1,i,i);
}

MatrixBase::MatrixBase(const std::string& filename) : IntegerTable(filename){/* Do nothing */}

std::vector<int> MatrixBase::vector_product(std::vector<int> v, std::vector<int> w)
{
    std::vector<int> out;
    size_t common = v.size();
    if (w.size() == common)
    {
        for(size_t i = 0; i < common; i++)
        {
            out.push_back(v[i] * w[i]);
        }
        return out;
    }
    else{
        throw "Vectors are not compatible.";
    }
}

int MatrixBase::dot_product(std::vector<int> v, std::vector<int> w)
{
    return this->sum(vector_product(v,w));
}

int MatrixBase::sum(std::vector<int> v)
{
    int total = 0;
    for(size_t i = 0; i < v.size(); i++)
    {
        total += v[i];
    }
    return total;
}

#endif // MATRIX_BASE_H_INCLUDED