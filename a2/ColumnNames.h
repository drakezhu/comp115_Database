#pragma once

#include <vector>
#include <string>

using namespace std;

class ColumnNames : public vector<string>
{
public:
    int position(const string &name) const;

    ColumnNames();

    ColumnNames(const ColumnNames &columns);

    ColumnNames(initializer_list<string> elements);
};
