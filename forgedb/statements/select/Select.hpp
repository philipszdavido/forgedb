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
    //    groupBy;
    //    having;
    //    orderBy;
    //    selFlags;
    int limit;
    int offset;
    
    Select() = default;
    
    Select(Select&&) = default;
    Select& operator=(Select&&) = default;
    
    Select(const Select&) = delete;
    Select& operator=(const Select&) = delete;
};

#endif /* Select_hpp */
