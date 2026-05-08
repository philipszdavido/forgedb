//
//  vm.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 03/05/2026.
//

#ifndef vm_hpp
#define vm_hpp

#include <stdio.h>
#include "vm/chunk/Chunk.hpp"
#include "vm/opcode/opcode.hpp"
#include "plan-pipeline/plans/BasePlan/Plan.hpp"

void runVM(unordered_map<string, Table>& db, const Chunk* chunk);

class Rabbit {

public:
    Rabbit(unordered_map<string, Table>& db) : db(db) {};
    void run();
    void setChunk(const Chunk* c);
    
private:
    int pc = 0;
    bool running = true;
    
    int rowIndex = 0;
    vector<Value> stack;
    const Chunk* chunk;
    Table* table;
    Table tempTable;
    unordered_map<string, Table>& db;
    
    Row* currentRow = nullptr;
    
    Value pop();
    void push(Value x);
};

#endif /* vm_hpp */
