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
    
    if (stmt.column.isStar) {
        plan = make_unique<StarColumnProjectionPlan>(std::move(plan));
    } else if (stmt.column.isSelect) {
        
    } else {
        plan = make_unique<ProjectionPlan>(std::move(plan),
                                           stmt.column.columns);
    }
    
    if (stmt.limit >= 0) {
        plan = make_unique<LimitPlan>(std::move(plan), stmt.limit);
    }
    
    return plan;
}
