#pragma once

class Row;

class RowCompare
{
public:
    int operator()(Row* const &x, Row* const &y);
};
