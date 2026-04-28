//
//  Planner.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 26/04/2026.
//

#ifndef Planner_hpp
#define Planner_hpp

#include <stdio.h>
#include "plan-pipeline/plans/BasePlan/Plan.hpp"
#include "statements/select/Select.hpp"

unique_ptr<Plan> buildPlan(const Select& stmt);

#endif /* Planner_hpp */
