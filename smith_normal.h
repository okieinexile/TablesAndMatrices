#ifndef SMITH_NORMAL_H
#define SMITH_NORMAL_H

#include <iostream>
#include"matrix.h"
#include <string>
#include"divisors.h"

struct Index
{
	int row;
	int column;
};


class SmithNormal
{

	public:
		Matrix base_matrix;
		Matrix M;
		Matrix U;
		Matrix V;

		SmithNormal(const std::string& filename)
		{
			Matrix out(filename);
			this->base_matrix = out;
			this->M = out.copy();
			this->U = this->M.left_identity();
			this->V = this->M.right_identity();
		}

		SmithNormal(Matrix public_matrix)
		{
			this->base_matrix = public_matrix;
			this->M = this->base_matrix.copy();
			this->U = this->M.left_identity();
			this->V = this->M.right_identity();
		}

		int rows(void)
		{
			return base_matrix.rows;
		}

		int columns(void)
		{
			return base_matrix.columns;
		}

        void algorithm(void)
        {
            int top = 0;
            Index pivot = this->find_pivot(top);
            if (pivot.row == -1)
            {
                throw "No pivot found!";
            }
            this->pivot_into_place(pivot.row, pivot.column, top);
            while(pivot.row >= 0)
            {
                while(!this->pivot_zeroed(top))
                {
                this->improve_pivot_down(top);
                this->improve_pivot_right(top);
                }
                top += 1;
                if (top < this->rows())
                {
                    pivot = this->find_pivot(top);
                }
                else
                {
                    break;
                }
            }
        }

        void pivot_into_place(int r, int c, int t)
        {
                this->M.swap_rows(r, t);
                this->U.swap_rows(r, t);
                this->M.swap_columns(c, t);
                this->V.swap_columns(c, t);
        }

		Index find_pivot(int index)
		{
			/* We are looking for a nonzero entry at or "below" (index, index)*/
			Index out;
			out.row = index;
			out.column = index;
			if(this->M.read_entry(out.row, out.column) != 0)
			{
				return out;
			}
			while(M.read_entry(out.row, out.column) == 0 && (out.column < this->columns()))
			{
				/* Look done column out.column for a non-zero entry*/
				while(this->M.read_entry(out.row, out.column) == 0 && (out.row < this->rows()))
				{
					out.row += 1;
					if (out.row < this->rows())
					{
						if (this->M.read_entry(out.row, out.column) != 0)
						{
							return out;
						}
					}
				}
				/* Having not found a nonzero entry in this column, move to the next column and start over*/
				out.row = index;
				out.column += 1;
				if (out.column < this->columns())
				{
					if (this->M.read_entry(out.row, out.column) !=0)
					{
						return out;
					}
				}
			}
			/* If no pivot was found return (-1,-1) saying so*/
			out.row = -1;
			out.column = -1;
			return out;
		}

		void improve_pivot_down(int i)
		{
		    if (!(i < this->rows()))
            {
                throw "Row index out of range!";
            }
            if (this->M.read_entry(i,i) ==0 )
            {
                throw "Cannot pivot on a zero entry!";
            }
            for(int j = i + 1; j< this->rows(); j++)
            {
                if (this->M.read_entry(j,i) == 0) continue;
                this->refine_row(i,j);
            }
		}

		void refine_row(int r1, int r2)
		{
			Divisors div(this->M.read_entry(r1, r1), this->M.read_entry(r2, r1));
			Bezout data = div.bezout();
			this->M.combine_rows(r1 , r2, data.s, data.t, -data.b / data.d, data.a / data.d );
			this->U.combine_rows(r1 , r2, data.s, data.t, -data.b / data.d, data.a / data.d );
		}

		void improve_pivot_right(int i)
		{
		    if (!(i < this->columns()))
            {
                throw "Column index out of range!";
            }
            if (this->M.read_entry(i,i) ==0 )
            {
                throw "Cannot pivot on a zero entry!";
            }
            for(int j = i + 1; j< this->columns(); j++)
            {
                if (this->M.read_entry(i,j) == 0) continue;
                this->refine_column(i, j);
            }

		}

		void refine_column(int c1, int c2)
		{
			Divisors div(this->M.read_entry(c1, c1), this->M.read_entry(c1, c2));
			Bezout data = div.bezout();
			this->M.combine_columns(c1 , c2, data.s, data.t, - data.b / data.d, data.a / data.d );
			this->U.combine_columns(c1 , c2, data.s, data.t, - data.b / data.d, data.a / data.d );
		}

		bool pivot_zeroed(int pivot)
		{
			return this->zeroes_below_pivot(pivot) && this->zeroes_rightof_pivot(pivot);
		}

		bool zeroes_below_pivot(int pivot)
		{
			if (pivot >= this->rows()) throw "Index out of bounds";
			if (pivot == this->rows() - 1) return true;
			for(int r = pivot + 1; r < this->rows(); r++)
			{
				if (this->M.read_entry(r, pivot) != 0) return false;
			}
			return true;
		}

		bool zeroes_rightof_pivot(int pivot)
		{
			if (pivot >= this->columns()) throw "Index out of bounds";
			if (pivot == this->columns()-1) return true;
			for(int c = pivot + 1; c < this->columns(); c++)
			{
				if (this->M.read_entry(pivot, c) != 0) return false;
			}
			return true;
		}

};


#endif
