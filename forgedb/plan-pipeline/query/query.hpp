//
//  query.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 28/04/2026.
//

#ifndef query_hpp
#define query_hpp

#include <stdio.h>
#include <iostream>

#include "statements/includes.h"
#include "plan-pipeline/plans/BasePlan/Plan.hpp"
#include "plan-pipeline/execution/executor/Executor.hpp"
#include "plan-pipeline/planner/Planner.hpp"

using namespace std;

void runQuery(Select& stmt, unordered_map<string, Table>& db);
void runStmtQuery(Statement* stmt, unordered_map<string, Table>& db);

#endif /* query_hpp */
