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
    Table* iTable = Database::new_table(Database::new_table_name(), r->columns());

    
    for (set<Row*,RowCompare>::iterator it=r->rows().begin();it!=r->rows().end();it++)
    {   
        if (s->has(*it))
        {   
            Row* tmp = new Row(iTable,*it);
            iTable->add(tmp);
        }
    
    }
    return iTable;
}

Table *diff(Table *r, Table *s)
{
    //IMPLEMENTi_ME()
    if (r->columns().size() != s->columns().size())
    {
        throw UnionIncompatibilityException("number of columns are not equal!");
    }
    Table* dTable = Database::new_table(Database::new_table_name(), r->columns());


    for (set<Row*,RowCompare>::iterator it=r->rows().begin();it!=r->rows().end();it++)
    {
        if (!(s->has(*it)))
        {
            Row* tmp = new Row(dTable,*it);
            dTable->add(tmp);
        }

    }
    return dTable;
}

Table *product(Table *r, Table *s)
{
    //IMPLEMENT_ME();
    auto n = r->columns().size();
    auto m = s->columns().size();
    ColumnNames col(s->columns());
    for (unsigned long i = 0; i < n; i++)
    {   
        for (unsigned long j = 0; j < m; j++)
        {   
            
            if (r->columns().at(i) == s->columns().at(j))
            {   
                throw TableException("Duplicate columns");
            }
        }
        col.emplace_back(r->columns().at(i));
    }
    Table* pTable = Database::new_table(Database::new_table_name(), col);

    for (set<Row*,RowCompare>::iterator it=r->rows().begin();it!=r->rows().end();it++)
    {   
        for (set<Row*,RowCompare>::iterator it2=s->rows().begin();it2!=s->rows().end();it2++)
        {   
            Row* tmp = new Row(pTable,*it);
            
            for (unsigned long i = 0; i < m; i++)
            {   
                tmp->append((*it2)->at(i));
            }
            pTable->add(tmp);
        }
    }
    
    return pTable;
}

Table *rename(Table *r, const NameMap &name_map)
{
    //IMPLEMENT_ME();
    if (name_map.size() == 0 or name_map.size() != r->columns().size())
    {
        throw TableException("size problem!");
    }
    ColumnNames* col = new ColumnNames();
    for(unsigned long i = 0; i < r->columns().size();i++)
    {
        auto it = name_map.find(r->columns().at(i));
        if (it == name_map.end())
        {
            delete col;
            throw TableException("column not found");
        }
        col->push_back(it->second);
    }
    r->reNameCol(col);
    delete col;
    return r;
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
