//
//  Binary.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 23/04/2026.
//

#include "Binary.hpp"

BinaryOp toBinaryOp(const string op) {
    
    BinaryOp binOp;
    
    if (op == "=") {
        binOp = BinaryOp::EQ;
    } else if (op == "!=") {
        binOp = BinaryOp::NEQ;
    } else if (op == "<=") {
        binOp = BinaryOp::LTE;
    } else if (op == ">=") {
        binOp = BinaryOp::GTE;
    } else if (op == "<") {
        binOp = BinaryOp::LT;
    } else if (op == ">") {
        binOp = BinaryOp::GT;
    } else if (op == "AND") {
        binOp = BinaryOp::AND;
    } else if (op == "OR") {
        binOp = BinaryOp::OR;
    } else {
        throw runtime_error("Invalid op");
    }
    
    return binOp;
}

std::string opToString(BinaryOp op) {
    switch(op) {
        case BinaryOp::GT: return ">";
        case BinaryOp::LT: return "<";
        case BinaryOp::EQ: return "==";
        case BinaryOp::AND: return "AND";
        case BinaryOp::OR: return "OR";
        default: return "?";
    }
}
