#ifndef FACTORS_H_INCLUDED
#define FACTORS_H_INCLUDED

#include"prime_list.h"
#include <map>

class Factors
{
public:
    unsigned int number;
    std::map<int, unsigned int> factorization;
    PrimeList primes;
    bool is_square_free;

    Factors(unsigned int composite)
    {
        this->number = composite;
        PrimeList p(this->number);
        this->primes = p;
        this->factor(composite);
        this->is_square_free = (this->max_exponent() <= 1);
    }

    void factor(unsigned int N)
    {
        for(unsigned int i = 0; i < this->primes.size(); ++i)
        {
            int p = this->primes[i];
            while(N%p == 0)
            {
                ++this->factorization[p];
                N = N / p;
            }
        }
    }

    unsigned int max_exponent(void)
    {
        unsigned int exp = 0;
        for(auto entry : this->factorization)
        {
            if (entry.second > exp) exp = entry.second;
        }
        return exp;
    }

    void show(void)
    {
        for(auto entry : this->factorization)
        {
            std::cout << entry.first << "**" << entry.second << std::endl;
        }
        std::cout << "======" << std::endl;
    }
};

#endif // FACTORS_H_INCLUDED
