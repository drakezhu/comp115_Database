#include "Database.h"
#include "Table.h"

const Table *Row::table() const
{
    return _table;
}

const string &Row::value(const string &column) const
{
    const ColumnNames &columns = _table->columns();
    unsigned long n = columns.size();
    for (unsigned i = 0; i < n; i++) {
        if (columns.at(i) == column) {
            return _values.at(i);
        }
    }
    throw RowException("Unknown column");
}

const string &Row::at(unsigned i) const
{
    return _values.at(i);
}

void Row::append(const string &value)
{
    _values.emplace_back(value);
}

unsigned long Row::size() const
{
    return _values.size();
}

Row::Row(const Table *table)
        : _table(table)
{}

Row::Row(const Table *table, const Row *r)
        : _table(table)
{

    for(unsigned int i = 0; i < r->size(); i++)
    {
        _values.emplace_back(r->at(i));
    }
}

Row::~Row()
{
    _values.clear();
}
