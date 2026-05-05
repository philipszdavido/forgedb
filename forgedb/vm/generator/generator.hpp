//
//  generator.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 03/05/2026.
//

#ifndef generator_hpp
#define generator_hpp

#include <stdio.h>
#include "statements/includes.h"
#include "vm/opcode/opcode.hpp"
#include "vm/chunk/Chunk.hpp"

class GeneratorOpCode {
public:
    void buildOpcodes(Select& stmt);
    void buildStmtOpcodes(Statement* stmt);
    Chunk chunk;
private:
    template<typename X>
    Value buildValue();
    
    int emit(uint8_t c);
    int emitCode(OpCode code);
    int emitConstant(Value v);
    int emitConstantInt(size_t i);
    
};

#endif /* generator_hpp */
