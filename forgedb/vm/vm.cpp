//
//  vm.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 03/05/2026.
//

#include "vm.hpp"

//Table users = {
//    { {"id", "1"}, {"name", "Alice"}, {"age", "25"} },
//    { {"id", "2"}, {"name", "Bob"},   {"age", "17"} },
//    { {"id", "3"}, {"name", "Eve"},   {"age", "30"} }
//};

void Rabbit::run() {
    
    while(running) {
        
        OpCode op = static_cast<OpCode>(chunk->code[pc++]);
        
        switch (op) {
            case OpCode::SetTable: {
                
                Value tableName = chunk->constant[chunk->code[pc++]];
                table = db[tableName.getStringValue()];
                
                break;
            }
                
            case OpCode::Push: {
                break;
            }
                
            case OpCode::SelectAllColumns: {
                break;
            }
                
            case OpCode::SelectColumn: {
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


