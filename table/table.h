#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include <vector>
#include <sstream>
#include <assert.h>
#include"table_structure.h"

template <typename T>
class Table : public TableStructure<T>
{
public:
    Table(void);
    Table(size_t r, size_t c);
    Table(std::vector<T> pvector, size_t row_number, size_t column_number);
    void append_row(std::vector<T> row_vector);
    void set_entry(T value, size_t r, size_t c);
    T read_entry(size_t r, size_t c);
    std::vector<T> copy_row(size_t r);
    std::vector<T> copy_column(size_t c);
};

template <typename T>
std::ostream &operator<<(std::ostream &ost, const Table<T> &table);

/*

DEFINITIONS

*/

template <typename T>
Table<T>::Table(void) : TableStructure<T>(0,0){/* Do Nothing*/}

template <typename T>
Table<T>::Table(size_t r, size_t c) : TableStructure<T>(r,c){/* Do Nothing */}

template <typename T>
Table<T>::Table(std::vector<T> pvector, size_t row_number, size_t column_number)
: TableStructure<T>(row_number, column_number)
{
    assert(row_number * column_number == pvector.size());
    for(size_t index = 0; index < pvector.size(); ++index) 
      this->enter_item(index, pvector[index]);
}

template <typename T>
void Table<T>::append_row(std::vector<T> row_vector)
{
  size_t current_rows = this->rows();
  if (this->rows() == 0) this->set_columns(row_vector.size());
  assert(this->columns() == row_vector.size());
  for(T item : row_vector) this->push(item);
  this->set_rows(current_rows + 1);
}

template <typename T>
void Table<T>::set_entry(T value, size_t r, size_t c)
{
  assert(r <= this->rows());
  assert(c <= this->columns());
  this->enter_item(r * this->columns() + c, value);
}

template <typename T>
T Table<T>::read_entry(size_t r, size_t c)
{
    assert(r <= this->rows());
    assert(c <= this->columns());
    return this->myentry(r * this->columns() + c);
}

template <typename T>
std::vector<T> Table<T>::copy_row(size_t r)
{
  assert(r < this->rows());
	std::vector<T> out;
	for(size_t c = 0; c < this->columns(); ++c)
	{
		out.push_back(this->read_entry(r, c));
	}
	return out;
}

template <typename T>
std::vector<T> Table<T>::copy_column(size_t c)
{
  assert(c < this->columns());
	std::vector<T> out;
	for(size_t r = 0; r < this->rows(); ++r)
	{
		out.push_back(this->read_entry(r, c));
	}
	return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &ost, Table<T>& table)
{
  for(size_t r = 0; r < table.rows(); ++r)
	{
		for(size_t c = 0; c < table.columns(); ++c)
		{
			std::stringstream mystream;
			std::string mystring;
			T entry = table.read_entry(r,c);
			mystream << entry;
			mystream >> mystring;
			ost << mystring;
			if(c < table.columns() - 1) ost << ",";
		}
		ost << std::endl;
	}
    
    return ost;
}

#endif // TABLE_H_INCLUDED
