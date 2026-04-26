//
//  Identifier.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 26/04/2026.
//

#ifndef Identifier_hpp
#define Identifier_hpp

#include <stdio.h>
#include <string>
#include "expressions/Expression/Expression.hpp"

using namespace std;

struct Identifier : public Expression {
public:
    string value;

    Identifier(const string& val) : value(val) {}

    string toString() const override {
        return "'" + value + "'";
    }
};

#endif /* Identifier_hpp */
