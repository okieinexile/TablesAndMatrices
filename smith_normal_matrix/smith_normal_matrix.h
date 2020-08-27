#ifndef SMITH_NORMAL_MATRIX_H_INCLUDED
#define SMITH_NORMAL_MATRIX_H_INCLUDED

#include"smith_normal_moves.h"

class SmithNormalMatrix : public SmithNormalMoves 
{
private:
  bool algorithm_done = false;

public:
  SmithNormalMatrix(const std::string& filename);
  SmithNormalMatrix(SmithNormalMoves snm);
  SmithNormalMatrix(MatrixGlobal mg);
  void algorithm(void);
  Matrix U(void);
  Matrix V(void);
  void save_matrices(const std::string filestem);
};

SmithNormalMatrix::SmithNormalMatrix(const std::string& filename) : SmithNormalMoves(filename){/*Do Nothing*/}
SmithNormalMatrix::SmithNormalMatrix(SmithNormalMoves snm) : SmithNormalMoves(snm.rows(), snm.columns())
{
  for(size_t r = 0; r < snm.rows(); ++r)
  {
    for(size_t c = 0; c < snm.columns(); ++c)
    {
      this->set_entry(snm.read_entry(r, c), r, c);
    }
  }
}

SmithNormalMatrix::SmithNormalMatrix(MatrixGlobal mg) : SmithNormalMoves(mg.rows(), mg.columns())
{
  for(size_t r = 0; r < mg.rows(); ++r)
  {
    for(size_t c = 0; c < mg.columns(); ++c)
    {
      this->set_entry(mg.read_entry(r, c), r, c);
    }
  }
}

void SmithNormalMatrix::algorithm(void)
{
    size_t top = 0;
    Index pivot = this->find_pivot(top);
    if (!pivot.pivot_found)
    {
        throw "No pivot found!";
    }

    this->algorithm_done = false;
    while(this->algorithm_done == false)
    {
        this->pivot_into_place(pivot.row, pivot.column, top);
        while(!this->pivot_zeroed(top))
        {
            this->improve_pivot_down(top);
            this->improve_pivot_right(top);
        }
        top += 1;
        if ( (top < this->rows()) && (pivot.column < this->columns()))
        {
            pivot = this->find_pivot(top);
        }
        else
        {
            break;
        }
        if (!(top < this->rows()) || !(top < this->columns())) this->algorithm_done = true;
    }
}

Matrix SmithNormalMatrix::U(void)
{
    Matrix out = this->left_identity();
    while(!row_ops.empty())
    {
        out = out * row_ops.top();
        row_ops.pop();
    }
    return out;
}

Matrix SmithNormalMatrix::V(void)
{
    Matrix out = this->right_identity();
    while(!column_ops.empty())
    {
        out = column_ops.top() * out;
        column_ops.pop();
    }
    return out;
}

void SmithNormalMatrix::save_matrices(const std::string filestem)
{
    std::string ufile = filestem + "_U.csv";
    std::string vfile = filestem + "_V.csv";
    std::string file = filestem + ".csv";
    this->to_csv(file);
    this->U().to_csv(ufile);
    this->V().to_csv(vfile);
}


#endif