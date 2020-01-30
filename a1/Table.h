#pragma once

#include <memory>
#include <set>
#include "Row.h"
#include "RowCompare.h"
#include "ColumnNames.h"
#include "Database.h"
#include<iostream>
using namespace std;

class RowSet: public set<Row*, RowCompare> {};

class Table
{
    friend Table* Database::new_table(const string &name, const ColumnNames &columns);

public:
    // The name of this Table
    const string &name() const;

    // The columns of this Table
    const ColumnNames &columns() const;

    // The contents of this Table
    const RowSet& rows();

    // Add the given row to the table, returning true if the row was added, false if not (because a matching row
    // is already present). Following a successful add (i.e., returning true), the row is owned by the table, and
    // must not be modified or deleted by the caller. Otherwise, it is the caller's responsibility to delete the row
    // eventually.
    bool add(Row* row);

    // Remove and delete a row matching the given row from this table. Return true if the row was found,
    // false if it wasn't.
    bool remove(Row* row);

    // Return true if a row matching the given row is present in the table, false otherwise.
    bool has(Row* row);

    // Destroy this table and delete its rows.
    ~Table();

private:
    // Create a table with the given name and column names
    Table(const string& name, const ColumnNames& columns);

private:
    string _name;
    ColumnNames _columns;
    RowSet _rows;
};
