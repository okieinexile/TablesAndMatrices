#include <iostream>
#include <assert.h>

#include"prime_list/prime_list.h"
#include <string>

int main(int argc, char** argv) 
{
  int ub = 100;
  try
  {
    PrimeList t(ub);
    std::cout << t[52] << std::endl;
    return 0;
  }
  catch(const char* e)
  {
    std::cerr << e << std::endl;
    return 1;
  }
}
