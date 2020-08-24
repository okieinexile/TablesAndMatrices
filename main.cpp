#include <iostream>
#include <assert.h>

#include"matrix/matrix.h"
#include <string>

int main(int argc, char** argv) 
{
  int s = 5;
  try
  {
    Matrix t(5,12);
    t.set_entry(7,0, 5);
    Matrix R = t.right_identity();
    Matrix L = t.left_identity();
    std::cout << L << std::endl;
    std::cout << t << std::endl;
    std::cout << R << std::endl;    
    Matrix M = L.multiply(t);
    Matrix N = t * R;
    std::cout << M << std::endl;
    std::cout << N << std::endl;
    return 0;
  }
  catch(const char* e)
  {
    std::cerr << e << std::endl;
    return 1;
  }
}
