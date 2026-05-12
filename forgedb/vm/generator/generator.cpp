//
//  generator.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 03/05/2026.
//

#include "generator.hpp"

void GeneratorOpCode::buildStmtOpcodes(Statement* stmt) {
    if (Select* select = dynamic_cast<Select*>(stmt)) {
        buildOpcodes(*select);
    }
}

void GeneratorOpCode::buildOpcodes(Select& stmt) {
    
//    Value x = stmt.table;
//    
//    int index = emitConstant(x);
    
    emitCode(OpCode::SetTable);
//    emit(index);

    int loop_start = emitCode(OpCode::SetCurrentRow);;
    
    int jump = -1;
    
//    if (stmt.where) {
//         buildExpression(stmt.where->expression.get());
//         emitCode(OpCode::JumpIfFalse);
//        jump = emit(0);
//    }
//    
//    if (stmt.column.isStar) {
//        emitCode(OpCode::SelectAllColumns);
//    } else if (stmt.column.isSelect) {
//        buildStmtOpcodes(stmt.column.selectColmun.get());
//    } else {
//        auto cols = stmt.column.columns;
//        
//        for (auto col : cols) {
//            Value v = col;
//            int index = emitConstant(v);
//            emitCode(OpCode::Push);
//            emit(index);
//        }
//        
//        emitCode(OpCode::SelectColumn);
//    }
    
    // we will jump to here
    if (jump > -1) {
        patchJump(jump);
    }
    
    emitCode(OpCode::IncrementRowIndex);

    emitCode(OpCode::Jump);
    emit(emitConstantInt(loop_start));
        
}

void GeneratorOpCode::buildExpression(Expression* expr) {
    eval(expr);
}


void GeneratorOpCode::eval(Expression* expr) {
    if (auto bin = dynamic_cast<BinaryExpression*>(expr)) {
        
        evalValue(bin->left.get());
        evalValue(bin->right.get());

        switch (bin->op) {
            case BinaryOp::EQ:
                emitCode(OpCode::Equal);
                break;
            case BinaryOp::GT:
                emitCode(OpCode::GreaterThan);
                break;
            case BinaryOp::GTE:
                emitCode(OpCode::GreaterThanOrEqual);
                break;
            case BinaryOp::LT:
                emitCode(OpCode::LessThan);
                break;
            case BinaryOp::LTE:
                emitCode(OpCode::LessThanOrEqual);
                break;
            case BinaryOp::AND:
                emitCode(OpCode::And);
                break;
            case BinaryOp::OR:
                emitCode(OpCode::Or);
                break;
            default:
                break;
        }
    }
}

void GeneratorOpCode::evalValue(Expression* expr) {
    
    if (auto id = dynamic_cast<Identifier*>(expr)) {
        
        emitCode(OpCode::Push);
        Value x = id->name;
        emit(emitConstant(x));
        
        emitCode(OpCode::GetColumnValue);
        
    } else if (auto lit = dynamic_cast<Literal*>(expr)) {
        
        emitCode(OpCode::Push);
        Value x = lit->value;
        emit(emitConstant(x));
        
    } else if (auto bin = dynamic_cast<BinaryExpression*>(expr)) {
        
        eval(bin);
        
    } else throw runtime_error("Invalid expression");
}

const Chunk* GeneratorOpCode::getChunk() const {
    return &chunk;
}

void GeneratorOpCode::patchJump(int index) {
    chunk.code[index] = (chunk.code.size() - 1);
}

int GeneratorOpCode::emitConstantInt(size_t i) {
    Value v = i;
    return emitConstant(i);
}

int GeneratorOpCode::emitCode(OpCode _code) {
    chunk.code.push_back((uint8_t)_code);
    return (int)chunk.code.size() - 1;
}

int GeneratorOpCode::emitConstant(Value v) {
    chunk.constants.push_back(v);
    return (int)chunk.constants.size() - 1;
}


int GeneratorOpCode::emit(uint8_t c) {
    chunk.code.push_back(c);
    return (int)chunk.code.size() - 1;
}
