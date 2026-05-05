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

enum class OpCode : uint8_t {
    SetTable,
    Push,
    SelectAllColumns,
    SelectColumn,
    Jump, // Jump index
    SetRowToTempTable,
    IncrementRowIndex,
    Halt
};

#endif /* opcode_hpp */
