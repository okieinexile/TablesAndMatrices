#ifndef CSV_TABLE_H
#define CSV_TABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include"../table/table.h"

class CSVTable : public Table<std::string>
{
	private:
		std::string myname;
		std::vector<std::string> lines;
		std::vector<std::string> split(const std::string& mstring);
	public:
    CSVTable(const std::string& filename);
    CSVTable(const std::vector<std::string> entries, size_t rows, size_t columns);
    void read_lines(void);
    void fill_entries(void);
    void save(const std::string& filename);
};

CSVTable::CSVTable(const std::string &filename) : Table()
{
	this->myname = filename;
	this->read_lines();
	this->fill_entries();
}

CSVTable::CSVTable(const std::vector<std::string> entries, size_t rows, size_t columns) : Table(entries, rows, columns){/* empty */}

void CSVTable::read_lines(void)
{
	std::string line;
	std::ifstream mfile(this->myname.c_str());
	if (mfile.is_open())
	{
		while(mfile.good())
		{
			getline(mfile, line);
			this->lines.push_back(line);
		}
		mfile.close();
	}
	else
	{
		std::cerr << this->myname << " did not open!";
	}
}

void CSVTable::fill_entries(void)
{
	for(size_t r = 0; r < this->lines.size(); ++r)
	{
		std::vector<std::string> new_row = split(this->lines[r]);
		if (new_row.size() > 0)
		{
			this->append_row(new_row);
		}

	}
}

void CSVTable::save(const std::string& filename)
{
	std::ofstream mfile(filename.c_str());
	for(size_t r = 0; r < this->rows(); ++r)
	{
		for(size_t c = 0; c < this->columns(); ++c)
		{
			mfile << this->read_entry(r,c);
			if (c < this->columns() - 1)
			{
				mfile << ",";
			}
		}
		mfile << std::endl;
	}
	mfile.close();
}

std::vector<std::string> CSVTable::split(const std::string& mstring)
{
	std::vector<std::string> output;
	std::istringstream ss(mstring);
	std::string token;
	while(std::getline(ss, token, ','))
	{
		output.push_back(token);
	}
	return output;
}


#endif
