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
#include "expressions/Binary/Binary.hpp"
#include "expressions/Literal/Literal.hpp"
#include "expressions/Identifier/Identifier.hpp"

class GeneratorOpCode {
public:
    void buildOpcodes(Select& stmt);
    void buildStmtOpcodes(Statement* stmt);
    void buildExpression(Expression* expr);
    const Chunk* getChunk() const;

private:
    Chunk chunk;

    // methods
    template<typename X>
    Value buildValue();
    
    int emit(uint8_t c);
    int emitCode(OpCode code);
    int emitConstant(Value v);
    int emitConstantInt(size_t i);
    
    void eval(Expression* expr);
    void evalValue(Expression* expr);
    
};

#endif /* generator_hpp */
