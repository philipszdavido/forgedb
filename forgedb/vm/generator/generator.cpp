//
//  generator.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 03/05/2026.
//

#include "generator.hpp"

void GeneratorOpCode::buildOpcodes(const Select& stmt) {
    
    Value x = stmt.table;
    
    int index = emitConstant(x);
    
    int tableIndex = emitCode(OpCode::SetTable);
    emit(index);
    
    int loop_start;
    
    emitCode(OpCode::Jump);
    emit(emitConstant(<#Value v#>));
    
}

template <typename X>
Value GeneratorOpCode::buildValue() {
    
}


int GeneratorOpCode::emitCode(OpCode _code) {
    code.push_back((uint8_t)_code);
    return (int)code.size() - 1;
}

int GeneratorOpCode::emitConstant(Value v) {
    constants.push_back(v);
    return (int)constants.size() - 1;
}


int GeneratorOpCode::emit(uint8_t c) {
    code.push_back(c);
    return (int)code.size() - 1;
}
