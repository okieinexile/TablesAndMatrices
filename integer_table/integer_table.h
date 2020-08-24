#ifndef INTEGER_TABLE_H_INCLUDED
#define INTEGER_TABLE_H_INCLUDED

#include <vector>
#include <sstream>
#include"../csv/csv_table.h"
#include <string>
#include"../table/table.h"


typedef std::vector<std::string> string_list;
typedef std::vector<int> int_list;


class IntegerTable : public Table<int>
{
	public:
	    IntegerTable(void);
	    IntegerTable(int r, int c);
	    IntegerTable(const std::string& filename);
	    void zeros(size_t r, size_t c);
		void to_csv(const std::string& filename);
		string_list to_string_vector(void);
};

IntegerTable::IntegerTable(void) : Table(){/* Do Nothing */}

IntegerTable::IntegerTable(int r, int c) : Table()
{
    this->zeros(r,c);
}

IntegerTable::IntegerTable(const std::string& filename)  : Table()
{
    CSVTable csv(filename);
    this->zeros(csv.rows(), csv.columns());
    for(size_t r = 0; r < csv.rows(); ++r)
    {
    	for(size_t c = 0; c < csv.columns(); ++c)
    	{
    		std::string string_entry = csv.read_entry(r, c);
    		/* Convert the string to an integer*/
			std::string mystring = "";
		    const char *dash = "-";
		    for(size_t i = 0; i < string_entry.size(); ++i)
		    {
		    	char c = string_entry[i];
	            if (isdigit(c)) mystring += c;
	            if ( c == *dash) mystring += c;
		    }
		    std::stringstream convert(mystring);
		    int integer_entry = 0;
		    convert >> integer_entry;
		    this->set_entry(integer_entry, r, c);
		}
	}
}

void IntegerTable::zeros(size_t r, size_t c)
{
    std::vector<int> zero_vector(c);
	for(size_t i = 0; i < r; ++i) this->append_row(zero_vector);
}

void IntegerTable::to_csv(const std::string& filename)
    {
        string_list string_vector = this->to_string_vector();
        CSVTable csv(string_vector, this->rows(), this->columns());
        csv.save(filename);

    }

string_list IntegerTable::to_string_vector(void)
    {
        string_list out_vector;
        for(size_t i = 0; i < this->rows() * this->columns(); ++i)
        {
            std::stringstream mystream;
            std::string mystring;
            mystream << this->myentry(i);
            mystream >> mystring;
            out_vector.push_back(mystring);
        }
        return out_vector;
    }



#endif // INTEGER_TABLE_H_INCLUDED
