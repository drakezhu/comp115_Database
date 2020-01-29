#pragma once

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Table;

class Row
{
public:
    // This Row's table
    const Table *table() const;

    // The value for the given column in this Row
    const string &value(const string &column) const;

    // The value for the ith column in this Row.
    const string &at(unsigned i) const;

    // Append a value to this Row
    void append(const string& value);

    // The number of values in this Row.
    unsigned long size() const;

    // Create a Row for the given Table
    Row(const Table *table);

    // Destroy this Row
    ~Row();

private:
    const Table *_table;
    // Add a data member to store the contents of the row
};
