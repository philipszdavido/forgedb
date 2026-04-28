//
//  Binary.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 23/04/2026.
//

#ifndef Binary_hpp
#define Binary_hpp

#include <stdio.h>
#include "expressions/Expression/Expression.hpp"

using namespace std;

enum class BinaryOp {
    EQ,     // =
    NEQ,    // !=
    GT,     // >
    LT,     // <
    GTE,    // >=
    LTE,    // <=
    AND,
    OR
};

class BinaryExpression : public Expression {
public:
    BinaryOp op;
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
    
    BinaryExpression(std::unique_ptr<Expression> l, BinaryOp o, std::unique_ptr<Expression> r) : left(std::move(l)), op(o), right(std::move(r)) {}
};

#endif /* Binary_hpp */
