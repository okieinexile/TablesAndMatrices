#ifndef BEZOUT_H_INCLUDED
#define BEZOUT_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>
#include"gcd.h"

class Bezout: public GCD
{
public:
  int s;
  int t;

Bezout(int pivot, int target);
void set_st(int mys, int myt);
};

std::ostream& operator<<(std::ostream& ost, Bezout bz);

Bezout::Bezout(int pivot, int target) : GCD(pivot, target)
{
  if (this->divides || this->is_divided_by)
  {
    if (this->divides)
          {
           this->set_st(1, 0);
          }
          else
          {
           this->set_st(0, 1);
          }
  }
  else
    {
        Quotient back = this->back();
        this->set_st(1, -back.quotient);
        this->pop_quotient();
        while(!this->empty())
        {
            back = this->back();
            int sp = this->t;
            int tp = this->s - this->t * back.quotient;
            this->set_st(sp, tp);
            this->pop_quotient();
        }
    }
  int combination = this->s * this->pivot + this->t * this->target;
  if (combination != this->gcd) throw "Error in Bezout!";
}

void Bezout::set_st(int mys, int myt)
{
  this->s = mys;
  this->t = myt;
}

std::ostream& operator<<(std::ostream& ost, Bezout bz)
{
  ost << bz.gcd << " = " << bz.s << " * " << bz.pivot 
      << " + " << bz.t << " * " << bz.target 
      << std::endl;
  return ost;
}

#endif // BEZOUT_H_INCLUDED
