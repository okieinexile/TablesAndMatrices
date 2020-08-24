#ifndef ROW_REDUCE_H_INCLUDED
#define ROW_REDUCE_H_INCLUDED

#include"matrix.h"

struct Index
{
	int row;
	int column;
};

class RowReduce
{
    private:
        Matrix M;
    public:

        RowReduce(Matrix pmatrix)
        {
            this->M = pmatrix;
        }

        void show(void)
        {
            this->M.show();
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
			while(this->read_entry(out.row, out.column) == 0 && (out.column < this->columns()))
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

		int rows(void)
		{
		    return this->M.rows;
		}
		int columns(void)
		{
		    return this->M.columns;
		}
		int read_entry(int r, int c)
		{
		    return this->M.read_entry(r, c);
		}


};

#endif // ROW_REDUCE_H_INCLUDED
