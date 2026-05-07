//
//  opcode.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 03/05/2026.
//

#ifndef opcode_hpp
#define opcode_hpp

#include <stdio.h>
#include <cstdint>

#define OPCODE_LIST(OP) \
    OP(SetTable) \
    OP(Push) \
    OP(SelectAllColumns) \
    OP(SelectColumn) \
    OP(Filter) \
    OP(SetRowToTempTable) \
    OP(IncrementRowIndex) \
    OP(GreaterThan) \
    OP(LessThan) \
    OP(GreaterThanOrEqual) \
    OP(LessThanOrEqual) \
    OP(Or) \
    OP(And) \
    OP(Equal) \
    OP(NotEqual) \
    OP(Jump) \
    OP(Halt)

enum OpCode {
    #define OP(name) name,
        OPCODE_LIST(OP)
    #undef OP
};

#endif /* opcode_hpp */
