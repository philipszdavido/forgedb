//
//  query.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 28/04/2026.
//

#include "query.hpp"

void runQuery(Select& stmt, unordered_map<string, Table>& db) {
    auto plan = buildPlan(stmt);
    auto exec = buildExecutor(plan.get(), db);

    Row row;
    while (exec->next(row)) {
        for (auto& [k, v] : row) {
            cout << k << ": " << v << " ";
        }
        cout << endl;
    }
}
