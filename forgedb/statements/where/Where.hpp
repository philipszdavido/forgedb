//
//  Where.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef Where_hpp
#define Where_hpp

#include <stdio.h>
#include "expressions/Expression/Expression.hpp"

enum Op {
    OR,
    AND
};

class Where {
public:
    Op op;
    std::unique_ptr<Expression> lhs;
    std::unique_ptr<Expression> rhs;
};

#endif /* Where_hpp */
