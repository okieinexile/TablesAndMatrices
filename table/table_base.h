#ifndef TABLE_BASE_H_INCLUDED
#define TABLE_BASE_H_INCLUDED

#include <vector>
#include <assert.h>
#include <sstream>

template <typename T>
class TableBase 
{
private:
  std::vector<T> entries;  

public:
  TableBase(void);
  void push(T entry);
  T myentry(size_t index);
  void enter_item(size_t index, T value);
  static T null_entry(void)
  {
  std::stringstream ss;
  int z = 0;
  ss << z;
  T zero;
  ss >> zero;
  return zero;
  }
};

template <typename T>
TableBase<T>::TableBase(void){/* Do nothing */}

template <typename T>
void TableBase<T>::push(T entry)
{
  this->entries.push_back(entry);
}

template <typename T>
T TableBase<T>::myentry(size_t index)
{
  return this->entries[index];
}

template <typename T>
void TableBase<T>::enter_item(size_t index, T value)
{
  this->entries[index] = value;
}


#endif