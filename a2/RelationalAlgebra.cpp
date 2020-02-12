#include <sstream>
#include <cstring>
#include "Database.h"
#include "Table.h"
#include "RelationalAlgebra.h"
#include "unittest.h"
#include<iostream>
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
    //unordered_map<string,string>::iterator it;
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
    //IMPLEMENT_ME();
    Table* sTable = Database::new_table(Database::new_table_name(), r->columns());
    for (set<Row*,RowCompare>::iterator it=r->rows().begin();it!=r->rows().end();it++)
    {
        if (predicate(*it))
        {
            Row* tmp = new Row(sTable,*it);
            sTable->add(tmp);
        }   
    }
    
    return sTable;
}

Table *project(Table *r, const ColumnNames &columns)
{
    //IMPLEMENT_ME();
    Table* pTable = Database::new_table(Database::new_table_name(), r->columns());
    if (columns.size() == 0)
    {
        throw TableException("Empty Columns!");
    }
    ColumnNames* col = new ColumnNames();
    vector<unsigned int> selectedCols;
    for (auto it = columns.begin(); it != columns.end();it++ )
    {
	unsigned int counter = 0;
	bool Added = false;
        for (auto it2 = r->columns().begin(); it2 != r->columns().end(); it2++, counter++)
        {
            bool areSame = true;

            if (((*it2).size()) != ((*it).size()))
            {
                continue;
            }
            for (unsigned i = 0; i < (*it).size(); i++)
            {
                if ((*it).at(i) != (*it2).at(i))
                {
                    areSame = false;
                    break;
                }
            }
 	    if (areSame)
            {
                col->push_back(*it);
                selectedCols.push_back(counter);
		Added = true;
            }
	}
        if (!Added)
        {
	    delete col;
            throw TableException("Column Unknown!");
        }
    }
    pTable->reNameCol(col);
    for (set<Row*,RowCompare>::iterator it=r->rows().begin();it!=r->rows().end();it++)
    {
        Row* tmp = new Row(pTable);
        for (auto it2 = selectedCols.begin(); it2 != selectedCols.end();it2++)
        {
            tmp->append((*it)->at(*it2));
        }
        unsigned size = pTable->rows().size();
        pTable->add(tmp);
        if (size == pTable->rows().size())
        {
            delete tmp;
        }
    }
    delete col; 
    return pTable;
}

Table *join(Table *r, Table *s)
{
    //IMPLEMENT_ME();
    ColumnNames col(r->columns());
    unsigned index_for_s = 0;
    vector<unsigned> v1;
    vector<unsigned> v2;
    for (auto i = s->columns().begin(); i != s->columns().end(); i++)
    {
        unsigned index_for_r = 0;
        bool unique = true;
        for (auto j = r->columns().begin(); j != r->columns().end();j++)
        {
            if (*i == *j)
            {
		unique = false;
                v1.push_back(index_for_r);
                v2.push_back(index_for_s);
            }
            index_for_r++;
        }
        index_for_s++;
	if (unique == true)
	{
	    col.push_back(*i);
	}
    }
    if (v1.size() == 0)
    {
        throw JoinException("No columns are matched!");
    }
    Table* jTable = Database::new_table(Database::new_table_name(), col);
    for(auto i = r->rows().begin(); i != r->rows().end(); i++)
    {
        for (auto j = s->rows().begin(); j != s->rows().end(); j++)
        {
            bool matched = true;
            for (unsigned index = 0; index < v1.size(); index++)
            {
                if (((*i)->at(v1.at(index))) != ((*j)->at(v2.at(index))))
                {
                    matched = false;
                    break;
                }
            }
            if (matched == true)
            {
                Row* tmp = new Row(jTable);
                for (unsigned id = 0; id < r->columns().size(); id++)
                {
                    tmp->append((*i)->at(id));
                }
                for (unsigned id = 0; id < s->columns().size();id++)
                {
		    auto isFind = v2.begin();
		    while( isFind != v2.end())
		    {
			if ((*isFind) == id)
			{
			    break;
			}
			isFind++;
		    }
                    if (isFind == v2.end())
                    {
                        tmp->append((*j)->at(id));
                    }
                }
                jTable->add(tmp);
            }
        }
    }
    return jTable;

}

