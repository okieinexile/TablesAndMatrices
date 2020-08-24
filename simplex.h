#ifndef SIMPLEX_H_INCLUDED
#define SIMPLEX_H_INCLUDED

#include"permutations.h"
#include <vector>
#include"factors.h"

class Simplex: public Permutation
{

public:
    int orientation;
    std::pair<long int,int> code;

    Simplex(std::vector<int> mvector, int sense) : Permutation(mvector)
    {
        if(abs(sense) != 1) throw "sense must be ether 1 or -1!";
        this->orientation = sense;
        this->code.first = this->id();
        this->code.second = (this->sign() * this->orientation);
    }

    Simplex(long int square_free) : Permutation(abs(square_free))
    {
            this->orientation = square_free / abs(square_free);
            this->code.first = abs(square_free);
            this->code.second = this->orientation;
    }

    bool operator==(Simplex other)
    {
        return (this->code == other.code);
    }


    unsigned int dimension(void)
    {
        return this->size() - 1;
    }

    void show_code(void)
    {
        std::cout << this->code.first << "  " << this->code.second << std::endl;
    }


};


#endif // SIMPLEX_H_INCLUDED
