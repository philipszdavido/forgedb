//
//  Literal.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 26/04/2026.
//

#ifndef Literal_hpp
#define Literal_hpp

#include <stdio.h>
#include <string>
#include "expressions/Expression/Expression.hpp"

using namespace std;

struct Literal : public Expression {
public:
    string value;

    Literal(const string& val) : value(val) {}

    string toString() const override {
        return "'" + value + "'";
    }
};

#endif /* Literal_hpp */
