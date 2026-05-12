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

class Where {
public:
    std::unique_ptr<Expression> expression;

    Where* clone() {
        
        auto where = new Where();
        
        where->expression = std::move(this->expression);
        
        return where;
        
    }
};

#endif /* Where_hpp */
