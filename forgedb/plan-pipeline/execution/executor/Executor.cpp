//
//  Executor.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 26/04/2026.
//

#include "Executor.hpp"

unique_ptr<Executor> buildExecutor(Plan* plan,
                                  unordered_map<string, Table>& db) {
    if (auto scan = dynamic_cast<ScanPlan*>(plan)) {
        return make_unique<ScanExecutor>(db[scan->table]);
    }

    if (auto filter = dynamic_cast<FilterPlan*>(plan)) {
        return make_unique<FilterExecutor>(
            buildExecutor(filter->input.get(), db),
                                           std::move(filter->predicate)
        );
    }

    if (auto proj = dynamic_cast<ProjectionPlan*>(plan)) {
        return make_unique<ProjectionExecutor>(
            buildExecutor(proj->input.get(), db),
            proj->columns
        );
    }

    if (auto limit = dynamic_cast<LimitPlan*>(plan)) {
        return make_unique<LimitExecutor>(
            buildExecutor(limit->input.get(), db),
            limit->limit
        );
    }

    throw runtime_error("Unknown plan node");
}
