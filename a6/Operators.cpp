#include <cassert>
#include <algorithm>
#include "QueryProcessor.h"
#include "Table.h"
#include "Index.h"
#include "Iterator.h"
#include "Row.h"
#include "ColumnSelector.h"
#include "Operators.h"
#include "util.h"

//----------------------------------------------------------------------

// TableIterator 

unsigned TableIterator::n_columns()
{
  return _table->columns().size();
}

void TableIterator::open()
{
  _input = _table->rows().begin();
  _end = _table->rows().end();

}

Row* TableIterator::next()
{
  Row * tmp = NULL;
  if (_input != _end)
  {   
    tmp = *_input;
    _input++;
  }
  return tmp;
}

void TableIterator::close()
{   
}
TableIterator::TableIterator(Table* table)
  : _table(table)
{   
  _input = table->rows().begin();
  _end = table->rows().end();
}

//----------------------------------------------------------------------

// IndexScan

unsigned IndexScan::n_columns()
{
    return IMPLEMENT_ME;
}

void IndexScan::open()
{
    IMPLEMENT_ME;
}

Row* IndexScan::next()
{
    return IMPLEMENT_ME;
}

void IndexScan::close()
{
    IMPLEMENT_ME;
}

IndexScan::IndexScan(Index* index, Row* lo, Row* hi)
    : _index(index),
      _lo(lo),
      _hi(hi == NULL ? lo : hi)
{}

//----------------------------------------------------------------------

// Select

unsigned Select::n_columns()
{
    return IMPLEMENT_ME;
}

void Select::open()
{
    IMPLEMENT_ME;
}

Row* Select::next()
{
    return IMPLEMENT_ME;
}

void Select::close()
{
    IMPLEMENT_ME;
}

Select::Select(Iterator* input, RowPredicate predicate)
    : _input(input),
      _predicate(predicate)
{
}

Select::~Select()
{
    delete _input;
}

//----------------------------------------------------------------------

// Project

unsigned Project::n_columns()
{
    return _column_selector.n_selected();
}

void Project::open()
{
    _input->open();
}

Row* Project::next()
{
    Row* projected = NULL;
    Row* row = _input->next();
    if (row) {
        projected = new Row();
        for (unsigned i = 0; i < _column_selector.n_selected(); i++) {
            projected->append(row->at(_column_selector.selected(i)));
        }
        Row::reclaim(row);
    }
    return projected;
}

void Project::close()
{
    _input->close();
}

Project::Project(Iterator* input, const initializer_list<unsigned>& columns)
    : _input(input),
      _column_selector(input->n_columns(), columns)
{}

Project::~Project()
{
    delete _input;
}

//----------------------------------------------------------------------

// NestedLoopsJoin

unsigned NestedLoopsJoin::n_columns()
{
    return IMPLEMENT_ME;
}

void NestedLoopsJoin::open()
{
    IMPLEMENT_ME;
}

Row* NestedLoopsJoin::next()
{
    return IMPLEMENT_ME;
}

void NestedLoopsJoin::close()
{
    IMPLEMENT_ME;
}

NestedLoopsJoin::NestedLoopsJoin(Iterator* left,
                                 const initializer_list<unsigned>& left_join_columns,
                                 Iterator* right,
                                 const initializer_list<unsigned>& right_join_columns)
    : _left(left),
      _right(right),
      _left_join_columns(left->n_columns(), left_join_columns),
      _right_join_columns(right->n_columns(), right_join_columns),
      _left_row(NULL)
{
    assert(_left_join_columns.n_selected() == _right_join_columns.n_selected());
}

NestedLoopsJoin::~NestedLoopsJoin()
{
    delete _left;
    delete _right;
    Row::reclaim(_left_row);
}

//----------------------------------------------------------------------

// Sort

unsigned Sort::n_columns() 
{
    return IMPLEMENT_ME;
}

void Sort::open() 
{
    IMPLEMENT_ME;
}

Row* Sort::next() 
{
    return IMPLEMENT_ME;
}

void Sort::close() 
{
    IMPLEMENT_ME;
}

Sort::Sort(Iterator* input, const initializer_list<unsigned>& sort_columns)
    : _input(input),
      _sort_columns(sort_columns)
{}

Sort::~Sort()
{
    delete _input;
}

//----------------------------------------------------------------------

// Unique

unsigned Unique::n_columns()
{
    return IMPLEMENT_ME;
}

void Unique::open() 
{
    IMPLEMENT_ME;
}

Row* Unique::next()
{
    return IMPLEMENT_ME;
}

void Unique::close() 
{
    IMPLEMENT_ME;
}

Unique::Unique(Iterator* input)
    : _input(input),
      _next_unique(NULL)
{}

Unique::~Unique()
{
    delete _input;
}
