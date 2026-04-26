//
//  Expression.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 22/04/2026.
//

#ifndef Expression_hpp
#define Expression_hpp

#include <stdio.h>
#include <string>

class Expression {
public:
    virtual ~Expression() = default;
    virtual std::string toString() const = 0;
};

#endif /* Expression_hpp */
