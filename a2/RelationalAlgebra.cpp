#include <sstream>
#include <cstring>
#include "Database.h"
#include "Table.h"
#include "RelationalAlgebra.h"
#include "unittest.h"

Table *onion(Table *r, Table *s)
{
    IMPLEMENT_ME();
    return NULL;
}

Table *intersect(Table *r, Table *s)
{
    IMPLEMENT_ME();
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
