#pragma once

class Row;

/*
RowSet is a std::set<Row*, RowCompare>. RowCompare is used by
std::set to implement the comparison of set elements to determine
equality. In a set, elements are unique as determined by
RowCompare. Rows are considered equal if they have the same values
in the same order.
*/

class RowCompare
{
public:
    int operator()(Row* const &x, Row* const &y);
};
