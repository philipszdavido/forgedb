//
//  Binary.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 23/04/2026.
//

#ifndef Binary_hpp
#define Binary_hpp

#include <stdio.h>
#include "../includes.h"

class Binary : public Expression {
    Expression lhs;
    Expression rhs;
};

#endif /* Binary_hpp */
