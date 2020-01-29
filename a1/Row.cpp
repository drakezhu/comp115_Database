#include "Database.h"
#include "Table.h"

const Table *Row::table() const
{
    return _table;
}

const string &Row::value(const string &column) const
{
    IMPLEMENT_ME();
    return *new string("");
}

const string &Row::at(unsigned i) const
{
    IMPLEMENT_ME();
    return *new string("");
}

void Row::append(const string &value)
{
    IMPLEMENT_ME();
}

unsigned long Row::size() const
{
    IMPLEMENT_ME();
    return 0;
}

Row::Row(const Table *table)
        : _table(table)
{}

Row::~Row()
{
    IMPLEMENT_ME();
}
