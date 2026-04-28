//
//  eval.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 28/04/2026.
//

#ifndef eval_hpp
#define eval_hpp

#include <stdio.h>
#include <string>

#include "expressions/includes.h"
#include "plan-pipeline/plans/BasePlan/Plan.hpp"

bool eval(Expression* expr, const Row& row);
std::string evalValue(Expression* expr, const Row& row);

#endif /* eval_hpp */
