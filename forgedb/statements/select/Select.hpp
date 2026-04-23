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

#include "../statement/Statement.hpp"
#include "./../where/Where.hpp"

using namespace std;

class Select : Statement {
    string table;
    vector<string> columns;
    Where where;
    // limit
};

#endif /* Select_hpp */
