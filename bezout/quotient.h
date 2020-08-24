#ifndef  QUOTIENT_H_INCLUDED
#define QUOTIENT_H_INCLUDED

#include <iostream>

class Quotient
{
public:
  int dividend;
  int divisor;
  int quotient;
  int remainder;
      bool divides;
  bool is_divided_by;

  Quotient(void);
  Quotient(int a, int b);
};

std::ostream& operator<<(std::ostream& ost, Quotient qt);

Quotient::Quotient(void){/* Do Nothing*/}

Quotient::Quotient(int a, int b)
{
  if( b == 0)
  {
    throw "Cannot divide by zero!";
  }
  this->dividend = a;
  this->divisor = b;
  this->quotient = a / b;
  this->remainder = a%b;
  this->is_divided_by = (this->remainder ==0);
        if(this->dividend == 0)
        {
            this->divides = false;
        }
        else
        {
            this->divides = (b%a == 0);
        }
}

std::ostream& operator<<(std::ostream& ost, Quotient qt)
{
  ost << qt.dividend << " = " << qt.quotient << " * " << qt.divisor
                      << " + " << qt.remainder << std::endl;
  return ost;
}

#endif