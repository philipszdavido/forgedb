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
    unique_ptr<Expression> lhs;
    unique_ptr<Expression> rhs;
    
    BinaryExpression(std::unique_ptr<Expression> l, BinaryOp o, std::unique_ptr<Expression> r) : lhs(std::move(l)), op(o), rhs(std::move(r)) {}
};

#endif /* Binary_hpp */
