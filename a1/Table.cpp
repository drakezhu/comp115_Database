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
    IMPLEMENT_ME();
}

Table::~Table()
{
    IMPLEMENT_ME();
}
