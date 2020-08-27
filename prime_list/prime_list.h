#ifndef PRIME_LIST_H_INCLUDED
#define PRIME_LIST_H_INCLUDED

#include <vector>
#include <iostream>
class PrimeList
{
private:
  std::vector<int> primes;
public:
  PrimeList(void);
  PrimeList(size_t upper_bound); 
  int read_entry(int index );
  int operator[](size_t index);
  int max(void);
  size_t prime_order(int prime_number);
  size_t size(void);
};
std::ostream& operator<<(std::ostream& ost, PrimeList plist);

PrimeList::PrimeList(void){ /*Do Nothing*/ }

PrimeList::PrimeList(size_t number_of_primes)
{
  primes.push_back(2);
  size_t prime_counter = 0;
  int prime_candidate = 3;

  while(prime_counter < number_of_primes)
  {
      bool has_divisor = false;
      for(auto p: primes)
      {
          if(prime_candidate%p == 0)
          {
              has_divisor = true;
              break;
          }
      }
      if(!has_divisor)
      {
          primes.push_back(prime_candidate);
          ++prime_counter;
      }
      ++prime_candidate;

  }
}

int PrimeList::read_entry(int index )
    {
        return this->primes[index];
    }

int PrimeList::operator[](size_t index)
    {
        return this->primes[index];
    }   

int PrimeList::max(void)
    {
        return this->primes.back();
    }

size_t PrimeList::prime_order(int prime_number)
{
  if (prime_number > this->max()) throw "Too large for this prime list!";
  for(size_t i = 0; i < this->primes.size(); ++i)
  {
      if (prime_number == this->primes[i]) return i;
  }
  throw "Number input is not prime!";
}

size_t PrimeList::size(void)
    {
        return primes.size();
    }

std::ostream& operator<<(std::ostream& ost, PrimeList plist)
{
    for(size_t i = 0; i< plist.size(); ++i)
    {
        ost << plist.read_entry(i) << "  ";
        if((i + 1)%5 == 0) ost << std::endl;
    }
  return ost;
}

#endif // PRIME_LIST_H_INCLUDED
