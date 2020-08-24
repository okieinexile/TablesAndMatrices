#ifndef GRAPHS_H
#define GRAPHS_H

#include"CSVLibrary.h"
#include <string>
#include <vector>
#include"matrix.h"
#include"utility.h"
#include <iostream>

class GraphBits
{
public:
    std::vector<std::vector<int> >  connections;
    int max_node;

    GraphBits(CSVEntries entries)
    {
        this->max_node = 0;
        for(int r = 0; r < entries.rows(); r++)
        {
            std::vector<int> my_row;
            for(int c = 0; c < entries.columns(r); c++)
            {
                int entry = string_to_int(entries.read_entry(r,c));
                if (entry > this->max_node)
                {
                    this->max_node = entry;
                }
                my_row.push_back(entry);
            }
            this->connections.push_back(my_row);
        }
    }

    int entry(int r, int c)
    {
        return connections[r][c];
    }
    int rows(void)
    {
        return this->connections.size();
    }

    int items(int r)
    {
        return this->connections[r].size();
    }
};


class Graph
{
public:
    std::string filename;
    CSVLibrary csv;
    CSVEntries entries;
    Matrix incidence;
    int connected = 1;

    Graph(const std::string& pfilename)
    {
        this->filename = pfilename;
        CSVLibrary csv(this->filename);
        this->csv = csv;
        this->entries = csv.read_entries();
        this->incidence = this->make_incidence();
    }

    Matrix make_incidence(void)
    {
        GraphBits graph_bits(this->entries);
        Matrix out(graph_bits.max_node + 1, graph_bits.max_node + 1);
        for(int r = 0 ; r < graph_bits.rows(); r++)
        {
            for(int i = 1; i < graph_bits.items(r); i++)
            {
                out.set_entry(this->connected, graph_bits.entry(r,0),graph_bits.entry(r,i));
            }
        }
        return out;
    }
};


#endif // GRAPHS_H
