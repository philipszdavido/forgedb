//
//  Select.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef Select_hpp
#define Select_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "statements/statement/Statement.hpp"
#include "statements/where/Where.hpp"

using namespace std;

class Select;

struct TableColumn {
    bool isStar;
    bool isSelect;
    vector<string> columns;
    unique_ptr<Select> selectColmun;
    
    TableColumn() = default;
    
    TableColumn(TableColumn&&) = default;
    TableColumn& operator=(TableColumn&&) = default;
    
    TableColumn(const TableColumn&) = delete;
    TableColumn& operator=(const TableColumn&) = delete;
};

class Select : public Statement {
public:
    TableColumn column;
    string table;
    Where where;
    //    groupBy; // Separates rows into groups based on the values in the grouping columns
    //    having; // Filters out groups that don’t satisfy the search condition
    //    orderBy; // Sorts the results of prior clauses to produce final output
    //    selFlags;
    int limit = -1;
    int offset = -1;
    
    Select() = default;
    
    Select(Select&&) = default;
    Select& operator=(Select&&) = default;
    
    Select(const Select&) = delete;
    Select& operator=(const Select&) = delete;
};

#endif /* Select_hpp */
