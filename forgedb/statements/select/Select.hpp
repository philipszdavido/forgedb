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

#include "statements/includes.h"

using namespace std;

struct TableColumn {
    bool isStar;
    vector<string> columns;
};

class Select : Statement {
    string table;
    TableColumn column;
    Where where;
//    groupBy;
//    having;
//    orderBy;
//    selFlags;
    int limit;
    int offset;
};

#endif /* Select_hpp */
