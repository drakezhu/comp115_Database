#include <sstream>
#include <cstring>
#include "Database.h"
#include "Table.h"
#include "RelationalAlgebra.h"
#include "unittest.h"

Table *onion(Table *r, Table *s)
{
    //IMPLEMENT_ME();
    if (r->columns().size() != s->columns().size())
    {
        throw UnionIncompatibilityException("number of columns are not equal!");
    }
    RowSet _rows(r->rows());
    _rows.insert(s->rows().begin(), s->rows().end());
    Table* uTable = Database::new_table("Union", r->columns());
    auto it = _rows.begin();
    while (it != _rows.end())
    {
        uTable->add(*it);
        it = _rows.erase(it);
    }
    return uTable;
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
