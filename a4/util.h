#pragma once

class Table;

class NotYetImplementedException: public exception
{
public:
    NotYetImplementedException();

    const char *what() const throw();
};

void print_table(const char *label, Table *t);

void reset_database();

void IMPLEMENT_ME();

Table* IMPLEMENT_THIS_QUERY();
