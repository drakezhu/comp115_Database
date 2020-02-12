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
    return _rows;
}

bool Table::add(Row* row)
{
    const ColumnNames& source_columns = row->table()->columns();
    const ColumnNames& target_columns = _columns;
    if (row->size() != _columns.size()) {
        throw TableException("row size is wrong");
    }
    if (source_columns.size() != target_columns.size()) {
        throw TableException("source and target metadata incompatible");
    }
    auto outcome = _rows.insert((Row*)row);
    return outcome.second;
}

bool Table::remove(Row* row)
{
    if (row->size() != _columns.size()) {
        throw TableException("row size is wrong");
    }
    bool removed = false;
    auto i = _rows.find(row);
    if (i != _rows.end()) {
        auto victim = *i;
        _rows.erase(i);
        delete victim;
        removed = true;
    }
    return removed;
}

bool Table::has(Row* row)
{
    if (row->size() != _columns.size()) {
        throw TableException("row size is wrong");
    }
    auto i = _rows.find(row);
    return i != _rows.end();
}


void Table::reNameCol(ColumnNames* columns)
{
    _columns.clear();
    for (unsigned i = 0; i < columns->size(); i++)
    {
        _columns.push_back(columns->at(i));
    }
}

Table::Table(const string &name, const ColumnNames &columns)
    : _name(name),
      _columns(columns)
{
    if (columns.empty()) {
        throw TableException("No columns");
    }
    auto n = columns.size();
    for (unsigned long i = 0; i < n; i++) {
        for (unsigned long j = i + 1; j < n; j++) {
            if (columns.at(i) == columns.at(j)) {
                throw TableException("Duplicate columns");
            }
        }
    }
}

Table::~Table()
{
    auto i = _rows.begin();
    while (i != _rows.end()) {
        delete *i;
        i = _rows.erase(i);
    }
    _rows.clear();
}
