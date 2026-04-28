//
//  eval.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 28/04/2026.
//

#include "eval.hpp"

bool eval(Expression* expr, const Row& row) {
    if (auto bin = dynamic_cast<BinaryExpression*>(expr)) {
        string left = evalValue(bin->left.get(), row);
        string right = evalValue(bin->right.get(), row);

        switch (bin->op) {
            case BinaryOp::EQ: return left == right;
            case BinaryOp::GT: return stoi(left) > stoi(right);
            case BinaryOp::LT: return stoi(left) < stoi(right);
            case BinaryOp::AND:
                return eval(bin->left.get(), row) &&
                       eval(bin->right.get(), row);
            case BinaryOp::OR:
                return eval(bin->left.get(), row) ||
                       eval(bin->right.get(), row);
            default:
                return false;
        }
    }
    return false;
}

string evalValue(Expression* expr, const Row& row) {
    if (auto id = dynamic_cast<Identifier*>(expr)) {
        return row.at(id->name);
    }
    if (auto lit = dynamic_cast<Literal*>(expr)) {
        return lit->value;
    }
    throw runtime_error("Invalid expression");
}
