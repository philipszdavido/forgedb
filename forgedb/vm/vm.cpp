//
//  vm.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 03/05/2026.
//

#include "vm.hpp"

void runVM(unordered_map<string, Table>& db, const Chunk* chunk) {
    
    Rabbit vm(db);
        
    vm.setChunk(chunk);
    vm.run();
}

//Table users = {
//    { {"id", "1"}, {"name", "Alice"}, {"age", "25"} }, Row 1
//    { {"id", "2"}, {"name", "Bob"},   {"age", "17"} }, Row 2
//    { {"id", "3"}, {"name", "Eve"},   {"age", "30"} } Row 3
//};

void Rabbit::run() {
    
    while(running) {
        
        OpCode op = static_cast<OpCode>(chunk->code[pc++]);
        
        switch (op) {
            case OpCode::SetTable: {
                
                Value tableName = chunk->constants[chunk->code[pc++]];
                table = &db[tableName.getStringValue()];
                
                break;
            }
                
            case OpCode::Push: {
                
                Value v = chunk->constants[chunk->code[pc]];
                stack.push_back(v);
                
                break;
            }
                
            case OpCode::SelectAllColumns: {
                tempRow = (*table)[rowIndex];
                break;
            }
                
            case OpCode::SelectColumn: {
                Row projected;
                for (Value col : stack) {
                    std::string columnName = col.getStringValue();
                    projected[columnName] = (*table)[rowIndex][columnName];
                }
                tempRow = projected;
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
                
                if (rowIndex >= table->size()) {
                    return;
                }

                Value label = chunk->constants[chunk->code[pc++]];
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
                
    }
    
}

void Rabbit::setChunk(const Chunk* c) {
    chunk = c;
}
