#ifndef FACTORS_H_INCLUDED
#define FACTORS_H_INCLUDED

#include"../prime_list/prime_list.h"
#include <map>

class Factors
{
private:
  size_t number;
  std::map<int, size_t> factorization;
  PrimeList primes;

public:
  bool is_square_free;
  Factors(size_t composite);
  void factor(size_t N);
  size_t max_exponent(void);
  std::map<int, size_t> my_factors(void);
};
std::ostream& operator<<(std::ostream& ost, Factors f);

Factors::Factors(size_t composite)
{
    this->number = composite;
    PrimeList p(this->number);
    this->primes = p;
    this->factor(this->number);
    this->is_square_free = (this->max_exponent() <= 1);
}
void Factors::factor(size_t N)
    {
        for(size_t i = 0; i < this->primes.size(); ++i)
        {
            int p = this->primes[i];
            while(N%p == 0)
            {
                ++this->factorization[p];
                N = N / p;
            }
        }
    }

size_t Factors::max_exponent(void)
{
    size_t exp = 0;
    for(std::pair<int,size_t> entry : this->my_factors())
    {
        if (entry.second > exp) exp = entry.second;
    }
    return exp;
}

std::map<int, size_t> Factors::my_factors(void)
{
  return this->factorization;
}

std::ostream& operator<<(std::ostream& ost, Factors f)
{
  for(std::pair<int, size_t> entry : f.my_factors())
  {
    ost << entry.first << "**" << entry.second << std::endl;
  }
  ost << "======" << std::endl;
  return ost;
}

#endif // FACTORS_H_INCLUDED
