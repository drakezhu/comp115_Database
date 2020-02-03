#pragma once

#include <unordered_map>
#include "dbexceptions.h"
#include "util.h"

class Table;
class ColumnNames;

using namespace std;

class Database
{
public:
    // Returns a new, empty table, with the given name, and column names.
    static Table* new_table(const string &name, const ColumnNames &columns);

    // Delete all tables and rows, resulting an an empty database.
    static void delete_all_tables();

private:
    static unordered_map<string, Table*> _tables;
};
