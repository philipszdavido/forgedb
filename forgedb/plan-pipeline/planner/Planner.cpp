//
//  Planner.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 26/04/2026.
//

#include "Planner.hpp"

unique_ptr<Plan> buildPlan(const Select& stmt) {

    unique_ptr<Plan> plan = make_unique<ScanPlan>(stmt.table);
    
//    if (stmt.where) {
//        plan = make_unique<FilterPlan>(std::move(plan), unique_ptr<Expression>(stmt.where->clone()));
//    }
    
    plan = make_unique<ProjectionPlan>(std::move(plan), stmt.columns);
    
    if (stmt.limit >= 0) {
        plan = make_unique<LimitPlan>(std::move(plan), stmt.limit);
    }
    
    return plan;
}
