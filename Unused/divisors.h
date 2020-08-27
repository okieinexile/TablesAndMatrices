#ifndef DIVISORS_H
#define DIVISORS_H


#include <vector>
#include <string>
#include <iostream>



class Quotient
{
	public:
		int dividend;
		int divisor;
		int quotient;
		int remainder;


		Quotient(void) = default;

		Quotient(int a, int b)
		{
			if( b == 0)
			{
				throw "Cannot divide by zero!";
			}
			this->dividend = a;
			this->divisor = b;
			this->quotient = a / b;
			this->remainder = a%b;

		}


		void show(void)
		{
			std::cout << this->dividend << " = " << this->quotient << " * " << this->divisor << " + " << this->remainder << std::endl;
		}
};


class GCD{
		public:
			std::vector<Quotient> itinerary;
			int a;
			int b;
			int gcd;
			void show(void)
			{
				for(unsigned int i = 0; i < this->itinerary.size(); ++i )
				{
					this->itinerary[i].show();
				}
			}
};

class Bezout{
	public:
		int d;
		int a;
		int b;
		int s;
		int t;
		Bezout(GCD gcd)
		{
			this->a = gcd.a;
			this->b = gcd.b;
			this->d = gcd.gcd;
			std::vector<Quotient> data = gcd.itinerary;
			if ((this->b%this->a == 0) || (this->a%this->b == 0))
			{
			    if (this->b%this->a == 0)
                {
                this->s = 1;
                this->t = 0;
                }
                else
                {
                    this->s = 0;
                    this->t = 1;
                }
			}
			else
            {
                Quotient back = data.back();
                this->s =  1;
                this->t = - back.quotient;
                data.pop_back();
                while(!data.empty())
                {
                    back = data.back();
                    int sp = this->t;
                    int tp = this->s - this->t * back.quotient;
                    this->s = sp;
                    this->t = tp;
                    data.pop_back();
                }
            }
		}

		Bezout(void) = default;

		void show(void)
		{
			int combination = this->s * this->a + this->t * this->b;
			std::cout << this->d << " = " << this->s << " * " << this->a << " + " << this->t << " * " << this->b << std::endl;
			if (this->s * this->a + this->t * this->b == this->d)
            {
                std::cout<< "gcd = " << this->d << " combination = " << combination <<" Success!" << std::endl;
            }
            else
            {
                std::cout<< "gcd = " << this->d << " combination = " << combination <<" Failure!" << std::endl;
            }
		}
};

class Divisors
{
	public:
		int a;
		int b;
		Divisors(int a, int b)
		{
			if ((b == 0)|| (a==0)){
				throw "Neither argument can be zero!";
			}
			this->a = a;
			this->b = b;
		}

        Divisors(void) = default;
		bool divides(void)
		{
			return (b%a == 0);
		}

		bool divided_by(void)
		{
		    return (a%b == 0);
		}

	GCD gcd(void)
	{
		GCD out;
		out.a = this->a;
		out.b = this->b;
		Quotient Q(this->a, this->b);
		if (Q.remainder ==0)
        {
            out.gcd = this->b;
            if (abs(this->a) == abs(this->b))
            {
                out.gcd = this->a;
            }
        }
        else
        {
            out.itinerary.push_back(Q);
            while(Q.remainder != 0)
            {
                Q = Quotient(Q.divisor, Q.remainder);
                out.itinerary.push_back(Q);
            }
            out.gcd = Q.divisor;
            out.itinerary.pop_back();
        }
		return out;
	}

	Bezout bezout(void)
	{
		GCD gcd = this->gcd();
		Bezout out = Bezout(gcd);
		return out;
	}

};

#endif
