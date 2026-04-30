//
//  Plan.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 26/04/2026.
//

#ifndef Plan_hpp
#define Plan_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>

#include "expressions/includes.h"

using namespace std;

//Table users = {
//    { {"id", "1"}, {"name", "Alice"}, {"age", "25"} },
//    { {"id", "2"}, {"name", "Bob"},   {"age", "17"} },
//    { {"id", "3"}, {"name", "Eve"},   {"age", "30"} }
//};

using Row = unordered_map<string, string>;
using Table = vector<Row>;

class Expression;

struct Plan {
    virtual ~Plan() = default;
};

struct ScanPlan : Plan {
    string table;

    ScanPlan(const string& t) : table(t) {}
};

struct StarColumnProjectionPlan : Plan {
    unique_ptr<Plan> input;
    
    StarColumnProjectionPlan(unique_ptr<Plan> in)
        : input(std::move(in)) {}

};

struct SelectColumnProjectionPlan : Plan {
    unique_ptr<Plan> input;
    
    SelectColumnProjectionPlan(unique_ptr<Plan> in)
        : input(std::move(in)) {}

};

struct FilterPlan : Plan {
    unique_ptr<Plan> input;
    unique_ptr<Expression> predicate;

    FilterPlan(unique_ptr<Plan> in, unique_ptr<Expression> pred)
        : input(std::move(in)), predicate(std::move(pred)) {}
};

struct ProjectionPlan : Plan {
    unique_ptr<Plan> input;
    vector<string> columns;

    ProjectionPlan(unique_ptr<Plan> in, vector<string> cols)
        : input(std::move(in)), columns(std::move(cols)) {}
};

struct LimitPlan : Plan {
    unique_ptr<Plan> input;
    int limit;

    LimitPlan(unique_ptr<Plan> in, int l)
        : input(std::move(in)), limit(l) {}
};

#endif /* Plan_hpp */
