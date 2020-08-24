#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <sstream>
#include <cctype>

int string_to_int(const std::string& pstring)
{
    std::string mystring = "";
    const char *dash = "-";
    for(auto c : pstring)
    {
            if (isdigit(c)) mystring += c;
            if ( c == *dash) mystring += c;
    }
    std::stringstream convert(mystring);
    int x = 0;
    convert >> x;
    return x;
}

std::string int_to_string(int myint)
{
    std::stringstream ss;
    std::string outstring;
    ss << myint;
    ss >> outstring;
    return outstring;
}


#endif // UTILITY_H_INCLUDED
