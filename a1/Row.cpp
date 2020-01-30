#include "Database.h"
#include "Table.h"

const Table *Row::table() const
{
    return _table;
}

const string &Row::value(const string &column) const
{
    //IMPLEMENT_ME();
    
    for (unsigned i = 0; i < table()->columns().size();i++)
    {
	if (column.compare(table()->columns().at(i)) == 0)
        {
	    return vector::at(i);
	}
    }
    throw RowException("Column not found");
}

const string &Row::at(unsigned i) const
{
    //IMPLEMENT_ME();
    return vector::at(i);	
}

void Row::append(const string &value)
{
    //IMPLEMENT_ME();
    vector::push_back(value);
}

/*unsigned long Row::size() const
{
    //IMPLEMENT_ME();
    //cout << "test" << endl;
    //return this->size();
    return;
}*/

Row::Row(const Table *table)
        : _table(table)
{}

Row::~Row()
{
    //IMPLEMENT_ME();
    //delete _table;
}
