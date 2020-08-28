#include <iostream>
#include <assert.h>

#include"factors/factors.h"
#include <string>

int main(int argc, char** argv) 
{
  int ub = 9999;
  try
  {
    Factors f(ub);
    std::cout << f << std::endl;
    return 0;
  }
  catch(const char* e)
  {
    std::cerr << e << std::endl;
    return 1;
  }
}
