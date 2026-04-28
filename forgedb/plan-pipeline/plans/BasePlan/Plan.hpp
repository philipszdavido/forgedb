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

struct StarColumnPlan : Plan {};
struct VectorColumnPlan : Plan {};
struct SelectColumnPlan : Plan {};

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
