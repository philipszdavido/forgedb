//
//  Where.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef Where_hpp
#define Where_hpp

#include <stdio.h>
#include "../../Expression/Expression.hpp"

enum Op {
    OR,
    AND
};

class Where {
    Op op;
    Expression lhs;
    Expression rhs;
};

#endif /* Where_hpp */
