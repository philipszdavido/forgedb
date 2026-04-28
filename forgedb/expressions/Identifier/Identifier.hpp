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
    string name;

    Identifier(const string& val) : name(val) {}

    string toString() const override {
        return "'" + name + "'";
    }
};

#endif /* Identifier_hpp */
