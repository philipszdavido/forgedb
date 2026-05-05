//
//  vm.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 03/05/2026.
//

#include "vm.hpp"

void runVM(unordered_map<string, Table>& db, Chunk* chunk) {
    
    Rabbit vm(db);
        
    vm.setChunk(chunk);
    vm.run();
}

//Table users = {
//    { {"id", "1"}, {"name", "Alice"}, {"age", "25"} },
//    { {"id", "2"}, {"name", "Bob"},   {"age", "17"} },
//    { {"id", "3"}, {"name", "Eve"},   {"age", "30"} }
//};

void Rabbit::run() {
    
    while(running) {
        
        OpCode op = static_cast<OpCode>(chunk->code[pc++]);
        int rowIndex = 0;
        
        switch (op) {
            case OpCode::SetTable: {
                
                Value tableName = chunk->constants[chunk->code[pc]];
                *table = db[tableName.getStringValue()];
                
                break;
            }
                
            case OpCode::Push: {
                Value v = chunk->constants[chunk->code[pc++]];

                stack.push_back(v);
                break;
            }
                
            case OpCode::SelectAllColumns: {
                tempRow = tempTable[rowIndex];
                break;
            }
                
            case OpCode::SelectColumn: {
                Row projected;
                for (Value col : stack) {
                    projected[col.getStringValue()] = tempRow[col.getStringValue()];
                }
                break;
            }
                
            case OpCode::SetRowToTempTable: {
                tempTable.push_back(tempRow);
                break;
            }
                
            case OpCode::IncrementRowIndex: {
                rowIndex++;
                break;
            }
                
            case OpCode::Jump: {
                Value label = chunk->constants[chunk->code[pc]];
                pc = (int)label.getIntValue();
                break;
            }

            case OpCode::Halt: {
                running = false;
                break;
            }
                
            default:
                break;
        }
        
        pc++;
        
    }
    
}

void Rabbit::setChunk(Chunk* c) {
    chunk = c;
}
