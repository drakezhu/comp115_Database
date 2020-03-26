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
  return _index->n_columns();
}

void IndexScan::open()
{   
  _input = _index->begin();
  _end = _index->end();
}

Row* IndexScan::next()
{   
  Row * tmp = NULL;
  if (_input != _end)
  {   
    tmp = _input->second;
    _input++;
  }
  return tmp;
}

void IndexScan::close()
{   
}

IndexScan::IndexScan(Index* index, Row* lo, Row* hi)
    : _index(index),
      _lo(lo),
      _hi(hi == NULL ? lo : hi)
{
    for (auto it = _index->begin(); it != _index->end(); it++)
    {
        auto v = it->first;
        bool shouldRemove = false;
        for (unsigned i = 0; i < v.size(); i++)
        {
            if (v.at(i) < _lo->at(i) || v.at(i) > _hi->at(i))
            {
                shouldRemove = true;
                break;
            }
        }
        if (shouldRemove == true)
        {
            _index->erase(it);
        }
    }
}

//----------------------------------------------------------------------

// Select

unsigned Select::n_columns()
{   
    return _input->n_columns();
}

void Select::open()
{   
    _input->open();
}

Row* Select::next()
{
  Row* selected = NULL;
  Row* row = _input->next();
  while (row)
  {
    if (_predicate(row))
    {
      selected = new Row();
      for (unsigned i = 0; i < row->size();i++)
      {
        selected->append(row->at(i));
      }
      Row::reclaim(row);
      break;
    }
    row = _input->next();
  }
  return selected;
}

void Select::close()
{
    _input->close();
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
  return _left_join_columns.n_columns() + _right_join_columns.n_columns() - _right_join_columns.n_selected();
}

void NestedLoopsJoin::open()
{
  _left->open();
  _right->open();
  _left_row = _left->next();
}

Row* NestedLoopsJoin::join_rows_if_match(const Row* left, const Row* right)
{
  Row* tmp = new Row();
  for (unsigned i = 0; i < _left_join_columns.n_columns(); i++)
  {
    tmp->append(left->at(i));
  }
  for (unsigned i = 0; i < _right_join_columns.n_unselected(); i++)
  {
    tmp->append(right->at(_right_join_columns.unselected(i)));
  }
  return tmp;
}

Row* NestedLoopsJoin::next()
{
  Row* _right_row = _right->next();
  if (!_left_row || !_right_row)
  {
    return NULL;
  }
  while (_left_row)
  {
    if (!_right_row)
    {
      _left_row = _left->next();
      if (!_left_row)
      {
        return NULL;
      }
      _right->close();
      _right->open();
      _right_row = _right->next();
    }
    bool flag = true;
    for (unsigned i = 0; i < _right_join_columns.n_selected(); i++)
    {
      if (_left_row->at(_left_join_columns.selected(i)) != _right_row->at(_right_join_columns.selected(i)))
      {
        flag = false;
        break;
      }
    }
    if (flag == true)
    {
      return join_rows_if_match(_left_row, _right_row);
    }
    _right_row = _right->next();
  }
  return NULL;
}

void NestedLoopsJoin::close()
{
    _left->close();
    _right->close();
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
  return _sort_columns.size();
}

void Sort::open()
{
  _input->open();
  Row* row = _input->next();
  while (row)
  {
    bool done = false;
    for (auto it = _sorted.begin(); it != _sorted.end(); it++)
    {
        Row* r = *it;;
        bool append = false;
        for (unsigned i = 0; i < _sort_columns.size(); i++)
        {
          unsigned pos = _sort_columns.at(i);
          if (r->at(pos) == row->at(pos))
          {
            continue;
          }
          else if (r->at(pos) > row->at(pos))
          {
            append = true;
          }
          else
          {
            break;
          }
        }
        if (append == true)
        {
          _sorted.insert(it,row);
          done = true;
          break;
        }

    }
    if (done == false)
    {
      _sorted.emplace_back(row);
    }
    row = _input->next();
  }
  _sorted_iterator = _sorted.begin();

}

Row* Sort::next()
{
  Row* tmp = NULL;
  if (_sorted_iterator != _sorted.end())
  {
    tmp = *_sorted_iterator;
    _sorted_iterator++;
  }
  return tmp;

}
void Sort::close()
{
    _sorted.clear();
    _input->close();
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
  return _input->n_columns();
}

void Unique::open()
{
  _input->open();
}

Row* Unique::next()
{
  Row* row = _input->next();
  bool found = false;
  while (row)
  {
    if (!_next_unique)
    {
      _next_unique = row;
      found = true;
      break;
    }
    else
    {
      bool equal = true;
      for (unsigned i = 0; i < n_columns(); i++)
      {
        if (_next_unique->at(i) != row->at(i))
        {
          equal = false;
          break;
        }

      }
      if (equal == false)
      {
        _next_unique = row;
        Row::reclaim(row);
        found = true;
        break;
      }
    }
    row = _input->next();
  }
  if (found == false)
  {
        _next_unique = NULL;
    }
    return _next_unique;

}

void Unique::close()
{
    _input->close();
    _next_unique = NULL;
}

Unique::Unique(Iterator* input)
    : _input(input),
      _next_unique(NULL)
{}

Unique::~Unique()
{
    delete _input;
}
