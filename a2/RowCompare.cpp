#include <cstring>
#include <cassert>
#include "RowCompare.h"
#include "Row.h"
#include "Table.h"

int RowCompare::operator()(Row* const &x, Row* const &y)
{
    unsigned long n = x->size();
    assert(n == y->size());
    for (unsigned long i = 0; i < n; i++) {
        int comparison = strcmp(x->at(i).c_str(), y->at(i).c_str());
        if (comparison != 0) {
            return comparison < 0;
        }
    }
    return 0;
}
