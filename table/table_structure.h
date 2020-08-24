#ifndef TABLE_STRUCTURE_H_INCLUDED
#define TABLE_STRUCTURE_H_INCLUDED

#include"table_base.h"

template <typename T>
class TableStructure : public TableBase<T>
{
private:
  size_t nrows;
  size_t ncols;
  void fill_entries(void);
public:
  TableStructure(void);
  TableStructure(size_t rows, size_t columns);
  size_t rows(void);
  size_t columns(void);
  void set_rows(size_t rows);
  void set_columns(size_t columns);
  size_t number_of_entries(void);
};

template <typename T>
void TableStructure<T>::fill_entries(void)
{
  for(size_t i = 0; i < this->number_of_entries(); ++i)
  {
    this->push(TableBase<T>::null_entry());
  }
}

template <typename T>
TableStructure<T>::TableStructure(void) : TableBase<T>() {/* Do Nothing */}

template <typename T>
TableStructure<T>::TableStructure(size_t rows, size_t columns) : TableBase<T>()
{
  assert(rows >= 0);
  assert(columns >= 0);
  this->nrows = rows;
  this->ncols = columns;
  this->fill_entries();
}

template <typename T>
size_t TableStructure<T>::rows(void)
{
  return this->nrows;
}

template <typename T>
size_t TableStructure<T>::columns(void)
{
  return this->ncols;
}

template <typename T>
void TableStructure<T>::set_rows(size_t rows)
{
  this->nrows = rows;
}

template <typename T>
void TableStructure<T>::set_columns(size_t columns)
{
  this->ncols = columns;
}
template <typename T>
size_t TableStructure<T>::number_of_entries(void)
{
  return this->rows() * this->columns();
}


#endif
