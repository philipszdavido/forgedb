//
//  Disassembler.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 08/05/2026.
//

#ifndef Disassembler_hpp
#define Disassembler_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>

#include "vm/opcode/opcode.hpp"
#include "vm/chunk/Chunk.hpp"

class Disassembler {
public:
    static void disassemble(const Chunk* chunk) {
        size_t pc = 0;

        while (pc < chunk->code.size()) {
            pc = disassembleInstruction(chunk, pc);
        }
    }

private:

    static size_t disassembleInstruction(const Chunk* chunk, size_t pc) {
        std::cout << std::setw(4) << pc << " ";

        OpCode op = static_cast<OpCode>(chunk->code[pc++]);

        switch (op) {

            case OpCode::SetTable: {
                uint8_t constIndex = chunk->code[pc++];
                Value tableName = chunk->constants[constIndex];

                std::cout << "SetTable "
                          << tableName.getStringValue()
                          << "\n";
                break;
            }

            case OpCode::Push: {
                uint8_t constIndex = chunk->code[pc++];
                Value v = chunk->constants[constIndex];

                std::cout << "Push "
                          << valueToString(v)
                          << "\n";
                break;
            }

            case OpCode::SelectAllColumns:
                std::cout << "SelectAllColumns\n";
                break;

            case OpCode::SelectColumn:
                std::cout << "SelectColumn\n";
                break;

            case OpCode::SetRowToTempTable:
                std::cout << "SetRowToTempTable\n";
                break;

            case OpCode::SetCurrentRow:
                std::cout << "SetCurrentRow\n";
                break;

            case OpCode::IncrementRowIndex:
                std::cout << "IncrementRowIndex\n";
                break;

            case OpCode::GreaterThan:
                std::cout << "GreaterThan\n";
                break;

            case OpCode::LessThan:
                std::cout << "LessThan\n";
                break;

            case OpCode::GreaterThanOrEqual:
                std::cout << "GreaterThanOrEqual\n";
                break;

            case OpCode::LessThanOrEqual:
                std::cout << "LessThanOrEqual\n";
                break;

            case OpCode::Or:
                std::cout << "Or\n";
                break;

            case OpCode::And:
                std::cout << "And\n";
                break;

            case OpCode::Equal:
                std::cout << "Equal\n";
                break;

            case OpCode::NotEqual:
                std::cout << "NotEqual\n";
                break;

            case OpCode::GetColumnValue:
                std::cout << "GetColumnValue\n";
                break;

            case OpCode::JumpIfFalse: {
                uint8_t constIndex = chunk->code[pc++];
                Value label = chunk->constants[constIndex];

                std::cout << "JumpIfFalse -> "
                          << label.getIntValue()
                          << "\n";
                break;
            }

            case OpCode::Jump: {
                uint8_t constIndex = chunk->code[pc++];
                Value label = chunk->constants[constIndex];

                std::cout << "Jump -> "
                          << label.getIntValue()
                          << "\n";
                break;
            }

            case OpCode::Halt:
                std::cout << "Halt\n";
                break;

            default:
                std::cout << "Unknown opcode\n";
                break;
        }

        return pc;
    }

    static std::string valueToString(const Value& v) {
        return v.getStringValue();
        //        if (v.isString()) return "\"" + v.getStringValue() + "\"";
        //        if (v.isInt()) return std::to_string(v.getIntValue());
        //        if (v.isBool()) return v.getBoolValue() ? "true" : "false";
        //        return "<unknown>";
    }
};

#endif /* Disassembler_hpp */
