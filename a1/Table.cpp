#include "Table.h"

using namespace std;

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
    IMPLEMENT_ME();
    return *new RowSet();
}

bool Table::add(Row* row)
{
    IMPLEMENT_ME();
    return false;
}

bool Table::remove(Row* row)
{
    IMPLEMENT_ME();
    return false;
}

bool Table::has(Row* row)
{
    IMPLEMENT_ME();
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
}
