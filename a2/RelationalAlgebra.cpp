#include <sstream>
#include <cstring>
#include "Database.h"
#include "Table.h"
#include "RelationalAlgebra.h"
#include "unittest.h"

Table *onion(Table *r, Table *s)
{
    Table *onion(Table *r, Table *s)
    {
        //IMPLEMENT_ME();
        if (r->columns().size() != s->columns().size())
        {
            throw UnionIncompatibilityException("number of columns are not equal!");
        }
        Table* uTable = Database::new_table(Database::new_table_name(), r->columns());
        for(set<Row*,RowCompare>::iterator it=r->rows().begin();it!=r->rows().end();it++)
        {
            Row* tmp = new Row(uTable,*it);
            uTable->add(tmp);
        }
        for(set<Row*,RowCompare>::iterator it=s->rows().begin();it!=s->rows().end();it++)
        {
            Row* tmp = new Row(uTable,*it);
            unsigned len = uTable->rows().size();
            uTable->add(tmp);
            if (len == uTable->rows().size())
            {
                delete tmp;
            }

        }
        return uTable;
    }
}   

Table *intersect(Table *r, Table *s)
{
    //IMPLEMENT_ME();
    if (r->columns().size() != s->columns().size())
    {
        throw UnionIncompatibilityException("number of columns are not equal!");
    }
    
    return NULL;
}

Table *diff(Table *r, Table *s)
{
    IMPLEMENT_ME();
    return NULL;
}

Table *product(Table *r, Table *s)
{
    IMPLEMENT_ME();
    return NULL;
}

Table *rename(Table *r, const NameMap &name_map)
{
    IMPLEMENT_ME();
    return NULL;
}

Table *select(Table *r, RowPredicate predicate)
{
    IMPLEMENT_ME();
    return NULL;
}

Table *project(Table *r, const ColumnNames &columns)
{
    IMPLEMENT_ME();
    return NULL;
}

Table *join(Table *r, Table *s)
{
    IMPLEMENT_ME();
    return NULL;
}
