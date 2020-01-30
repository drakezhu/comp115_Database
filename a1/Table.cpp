#include "Table.h"
#include<algorithm>
using namespace std;
#include<iostream>
#include<set>
const string &Table::name() const
{
    return _name;
}

const ColumnNames &Table::columns() const
{
    return _columns;
}

const RowSet& Table::rows()
{
    //IMPLEMENT_ME();
    return _rows;
}

bool Table::add(Row* row)
{
    //IMPLEMENT_ME();
    if (row->size() != _columns.size())
    {
        throw TableException("Illegal row size");
	return false;
    }
    unsigned int old = _rows.size();
    _rows.insert(row);
    if (_rows.size() == old)
    {
	return false;
    }
    return true;
}
bool Table::remove(Row* row)
{
    //IMPLEMENT_ME();
    //RowCompare mycomp = _rows.value_comp(); 
    /*set<Row*,RowCompare>::iterator it = _rows.begin();
    while (it != _rows.end())
    {
	if (it == row)
	{
	    _rows.erase(it);
	    return true;
	}
	//throw RowException("cannot remove");
	it++;
	
    }
    int old = _rows.size(); 
    _rows.erase(row);
    if (_rows.size() != old)
    {
	return true;
    }*/
    unsigned int r_size = row->size();
    unsigned int c_size = _columns.size();
    if (r_size != c_size)
    {
        throw TableException("Row illegal!");
    }
    
    for (set<Row*,RowCompare>::iterator it = _rows.begin(); it != _rows.end(); it++)
    {
        Row single_row = **it;
        for (unsigned i = 0; i < r_size; i++)
        {
            if (single_row.at(i) != row->at(i))
            {
                break;
            }
            if (i == r_size - 1 && row->at(i) == single_row.at(i))
            {
		delete* it;
		_rows.erase(it);
		//delete row;
                return true;
            }
        }
    }    
    return false;
}

bool Table::has(Row* row)
{
    //IMPLEMENT_ME();
    unsigned int r_size = row->size();
    unsigned int c_size = _columns.size();
    if (r_size != c_size)
    {
	throw TableException("Row illegal!");
    }
    for (set<Row*,RowCompare>::iterator it = _rows.begin(); it != _rows.end(); it++)
    {
	Row single_row = **it;
	for (unsigned i = 0; i < r_size; i++)
	{
	    if (single_row.at(i) != row->at(i))
	    {
		break;
	    }
	    if (i == r_size - 1 && row->at(i) == single_row.at(i))
	    {
		return true;
	    }
	}
    }
    return false;
}

Table::Table(const string &name, const ColumnNames &columns)
    : _name(name),
      _columns(columns)
{
    //IMPLEMENT_ME();
    if (columns.empty()){
        throw TableException("Empty column");
    }
    ColumnNames tmp(columns);
    set<string> s;
    while (!tmp.empty())
    {
	s.insert(tmp.back());
	tmp.pop_back();	
    }
    if (s.size() != columns.size())
    {
	throw TableException("Duplicate columns");
    }
}

Table::~Table()
{
    //IMPLEMENT_ME();
    for (set<Row*,RowCompare>::iterator it = _rows.begin(); it != _rows.end(); it++)
    {
	delete *it;
	//it = _rows.erase(it);
    }
}
