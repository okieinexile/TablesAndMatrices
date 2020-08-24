#ifndef PERMUATIONS_H_INCLUDED
#define PERMUATIONS_H_INCLUDED

#include <vector>
#include <iostream>
#include <string>
#include"utility.h"
#include <set>
#include"prime_list.h"
#include"factors.h"
#include"integer_table.h"


class Permutation
{
private:
    std::vector<int> contents;
    std::set<int> elements;
    PrimeList primes;
    IntegerTable variations;
public:

    Permutation(void);
    Permutation(std::vector<int> pvector);
    Permutation(long int code);
    int fill_contents(std::vector<int> pvector);
    void append(int entry);
    size_t size(void);
    std::string repr(void);
    size_t parity(void);
    int sign(void);
    bool same_set(Permutation other);
    long int id(void);
    int operator[](size_t index );
    void generate(size_t k, Permutation A);
    void swap(size_t index1, size_t index2);
    IntegerTable all_permutations(void);
};

Permutation::Permutation(void){/* Do nothing */}

Permutation::Permutation(std::vector<int> pvector)
{
    int N = this->fill_contents(pvector);
    PrimeList p(N);
    this->primes = p;
}

Permutation::Permutation(long int code)
{
    Factors code_factors(code);
    if(!code_factors.is_square_free) throw "Can only make permutations with square-free integers!";
    std::vector<int> pvector;
    for(auto f : code_factors.factorization)
    {
        pvector.push_back(f.first);
    }
    int N = this->fill_contents(pvector);
    PrimeList p(N);
    this->primes = p;
}

int Permutation::fill_contents(std::vector<int> pvector)
{
    int N = 0;
    for(size_t i = 0; i < pvector.size(); ++i)
    {
        if(pvector[i] > N)
        {
            N = pvector[i];
        }
        this->append(pvector[i]);
    }
    return N;
}

void Permutation::append(int entry)
{
    if (this->elements.find(entry) != elements.end()) throw "Can only add distinct elements!";
    this->contents.push_back(entry);
    this->elements.insert(entry);
}

size_t Permutation::size(void)
{
    return this->contents.size();
}

std::string Permutation::repr(void)
{
    std::string out = "";
    for(auto entry: this->contents)
    {
        out += int_to_string(entry) + "  ";
    }
    return out;
}

size_t Permutation::parity(void)
{
    int exceeds = 0;
    for(size_t i = 0; i < this->size(); ++i)
    {
        int entry = this->contents[i];
        for(size_t j = i + 1; j < this->size(); ++j)
        {
            if (entry > this->contents[j]) ++exceeds;
        }
    }
    return exceeds%2;
}

int Permutation::sign(void)
{
    if(this->parity() == 0) return 1;
    if(this->parity() == 1) return -1;
    throw "Illegal Parity";
}

bool Permutation::same_set(Permutation other)
{
    return this->elements == other.elements;
}

long int Permutation::id(void)
{
    long int product = 1;
    for(size_t i = 0; i < this->size(); ++i)
    {
        size_t index = this->contents[i];
        long int prime_factor = this->primes.read_entry(index);
        product *= prime_factor;
    }
    return product;
}

int Permutation::operator[](size_t index )
{
 return this->contents[index];
}

std::ostream &operator<<(std::ostream &ost, Permutation permutation)
{
    ost << permutation.repr();
    return ost;
}

void Permutation::generate(size_t k, Permutation A)
{
    /* This implements Heap's Algorithm */
    if (k == 1)
    {
        this->variations.append_row(A.contents);
    }
    else
    {
        this->generate(k - 1, A);
        for(size_t i = 0; i < k -1; ++i)
        {
            if (k%2 == 0)
            {
                A.swap(i, k - 1);
            }
            else
            {
                A.swap(0, k -1);
            }
            this->generate(k-1, A);
        }
    }

}

void Permutation::swap(size_t index1, size_t index2)
{
    int bucket = this->contents[index1];
    this->contents[index1] = this->contents[index2];
    this->contents[index2] = bucket;
}

IntegerTable Permutation::all_permutations(void)
    {
        Permutation p(this->contents);
        this->generate(this->contents.size(), p);
        return this->variations;
    }


#endif // PERMUATIONS_H_INCLUDED
