#ifndef SMITH_NORMAL_MATRIX_H_INCLUDED
#define SMITH_NORMAL_MATRIX_H_INCLUDED

#include"matrix.h"
#include"bezout.h"
#include <bits/stdc++.h>

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


struct Index
{
	size_t row;
	size_t column;
	bool pivot_found = false;
};

class SmithNormalMatrix: public Matrix
{
private:
    std::stack <Matrix> row_ops;
    std::stack <Matrix> column_ops;
    bool algorithm_done = false;

public:
    SmithNormalMatrix(const std::string& filename);
    void algorithm(void);
    void improve_pivot_down(size_t i);
    void improve_pivot_right(size_t i);
    void refine_row(size_t r1, size_t r2);
    void refine_column(size_t c1, size_t c2);
    void pivot_into_place(size_t r, size_t c, size_t t);
    Index find_pivot(size_t index);
    bool pivot_zeroed(size_t pivot);
    bool zeroes_below_pivot(size_t pivot);
    bool zeroes_rightof_pivot(size_t pivot);
    Matrix U(void);
    Matrix V(void);
    void save_matrices(const std::string filestem);
} ;

SmithNormalMatrix::SmithNormalMatrix(const std::string& filename) : Matrix(filename){/* Do nothing */}

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

void SmithNormalMatrix::improve_pivot_down(size_t i)
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

void SmithNormalMatrix::improve_pivot_right(size_t i)
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

void SmithNormalMatrix::refine_row(size_t r1, size_t r2)
{
    Bezout data(this->read_entry(r1, r1), this->read_entry(r2, r1));
    RRMatrix rr(this->rows(), r1, r2, data);
    this->combine_rows(r1 , r2, data.s, data.t, -data.target / data.gcd, data.pivot / data.gcd );
    this->row_ops.push(rr);
}

void SmithNormalMatrix::refine_column(size_t c1, size_t c2)
{
    Bezout data(this->read_entry(c1, c1), this->read_entry(c1, c2));
    CRMatrix cr(this->columns(), c1, c2, data );
    this->combine_columns(c1 , c2, data.s, data.t, - data.target / data.gcd, data.pivot / data.gcd );
    this->column_ops.push(cr);
}

void SmithNormalMatrix::pivot_into_place(size_t r, size_t c, size_t t)
{
        RSMatrix rsm(this->rows(), r, t);
        CSMatrix csm(this->columns(), c, t);
        this->swap_rows(r, t);
        this->swap_columns(c, t);
        this->row_ops.push(rsm);
        this->column_ops.push(csm);
}

Index SmithNormalMatrix::find_pivot(size_t index)
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

bool SmithNormalMatrix::pivot_zeroed(size_t pivot)
{
    return this->zeroes_below_pivot(pivot) && this->zeroes_rightof_pivot(pivot);
}

bool SmithNormalMatrix::zeroes_below_pivot(size_t pivot)
{
    if (pivot >= this->rows()) throw "Index out of bounds";
    if (pivot == this->rows() - 1) return true;
    for(size_t r = pivot + 1; r < this->rows(); r++)
    {
        if (this->read_entry(r, pivot) != 0) return false;
    }
    return true;
}

bool SmithNormalMatrix::zeroes_rightof_pivot(size_t pivot)
{
    if (pivot >= this->columns()) throw "Index out of bounds";
    if (pivot == this->columns() - 1) return true;
    for(size_t c = pivot + 1; c < this->columns(); c++)
    {
        if (this->read_entry(pivot, c) != 0) return false;
    }
    return true;
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

#endif // SMITH_NORMAL_MATRIX_H_INCLUDED
