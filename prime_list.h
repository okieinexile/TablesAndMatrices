#ifndef PRIME_LIST_H_INCLUDED
#define PRIME_LIST_H_INCLUDED

#include <vector>
#include <iostream>
class PrimeList
{
public:
    std::vector<int> primes;

    PrimeList(void)
    {

    }

    PrimeList(int upper_bound)
    {
        primes.push_back(2);
        int prime_counter = 0;
        int prime_candidate = 3;

        while(prime_counter < upper_bound)
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

    int read_entry(int index )
    {
        return this->primes[index];
    }

    int operator[](unsigned int index)
    {
        return this->primes[index];
    }

    int max(void)
    {
        return this->primes.back();
    }

    unsigned int prime_order(int prime_number)
    {
        if (prime_number > this->max()) throw "Too large for this prime list!";
        for(unsigned int i = 0; i < this->primes.size(); ++i)
        {
            if (prime_number == this->primes[i]) return i;
        }
        throw "Number input is not prime!";
    }

    unsigned int size(void)
    {
        return primes.size();
    }

    void show(void)
    {
        for(auto p : this->primes)
        {
            std::cout << p << std::endl;
        }

    }

};

#endif // PRIME_LIST_H_INCLUDED
