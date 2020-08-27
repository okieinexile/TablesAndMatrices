#include <iostream>
#include <assert.h>

#include"smith_normal_matrix/smith_normal_matrix.h"
#include <string>

int main(int argc, char** argv) 
{
  int s = 5;
  try
  {
    SmithNormalMatrix t("paper_test.csv");
    SmithNormalMatrix s(t.transpose());
    std::cout << s << std::endl;
    t.algorithm();
    std::cout << t << std::endl;
    t.save_matrices("pt_matrix");
    return 0;
  }
  catch(const char* e)
  {
    std::cerr << e << std::endl;
    return 1;
  }
}
