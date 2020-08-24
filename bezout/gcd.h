#ifndef GCD_H_INCLUDED
#define GCD_H_INCLUDED

#include <vector>
#include"quotient.h"

class GCD: public Quotient
{
private:
  std::vector<Quotient> itinerary;

public:
  int pivot;
  int target;
  int gcd;
  GCD(int pivot, int target);
  void euclid(void);
  void push_quotient(Quotient quotient);
  void pop_quotient(void);
  bool empty(void);
  Quotient back(void);
  Quotient read_entry(size_t index);
  size_t steps(void);

};

std::ostream& operator<<(std::ostream& ost, GCD g);

GCD::GCD(int pivot, int target) : Quotient(pivot, target)
{
    if((pivot == 0) || (target == 0)) throw "Neither pivot nor target can be zero!";
    this->pivot = pivot;
    this->target = target;
    this->euclid();
}

void GCD::euclid(void)
{
    Quotient Q(this->pivot, this->target);
    if (Q.remainder == 0)
    {
        this->gcd = this->target;
        if (abs(this->pivot) == abs(this->target))
        {
            this->gcd = this->pivot;
        }
    }
    else
    {
        this->push_quotient(Q);
        while(Q.remainder != 0)
        {
            Q = Quotient(Q.divisor, Q.remainder);
            this->push_quotient(Q);
        }
        this->gcd = Q.divisor;
        this->pop_quotient();
    }
  }

void GCD::push_quotient(Quotient quotient)
  {
      this->itinerary.push_back(quotient);
  }  

void GCD::pop_quotient(void)
  {
      this->itinerary.pop_back();
  }

bool GCD::empty(void)
  {
      return this->itinerary.empty();
  }

Quotient GCD::back(void)
{
    return this->itinerary.back();
}  

Quotient GCD::read_entry(size_t index)
{
  return this->itinerary[index];
}

size_t GCD::steps(void)
{
  return this->itinerary.size();
}

std::ostream& operator<<(std::ostream& ost, GCD g)
{
  ost << "Pivot = " << g.pivot << std::endl;
  ost << "Target = " << g.target << std::endl;
  ost << "GCD = " << g.gcd << std::endl;
  for(unsigned int i = 0; i < g.steps(); ++i )
  {
      ost << g.read_entry(i);
  }
  ost << std::endl;
  return ost;
}

#endif