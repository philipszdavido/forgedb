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
    
    Value x = stmt.table;
    
    int index = emitConstant(x);
    
    emitCode(OpCode::SetTable);
    emit(index);
    
    int loop_start;
    
    if (stmt.column.isStar) {
        loop_start = emitCode(OpCode::SelectAllColumns);
    } else if (stmt.column.isSelect) {
        
    } else {
        auto cols = stmt.column.columns;
        loop_start = (int)chunk.code.size();
        
        for (auto col : cols) {
            Value v = col;
            int index = emitConstant(v);
            emitCode(OpCode::Push);
            emit(index);
        }
        
        emitCode(OpCode::SelectColumn);
    }

    emitCode(OpCode::SetRowToTempTable);
    emitCode(OpCode::IncrementRowIndex);

    emitCode(OpCode::Jump);
    emit(emitConstantInt(loop_start));
        
}

template <typename X>
Value GeneratorOpCode::buildValue() {
    
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
