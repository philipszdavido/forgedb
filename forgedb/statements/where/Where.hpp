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
    
    Where* clone() {
        
        auto where = new Where();
        
        where->op = this->op;
        where->lhs = std::move(this->lhs);
        where->rhs = std::move(this->rhs);
        
        return where;
        
    }
};

#endif /* Where_hpp */
