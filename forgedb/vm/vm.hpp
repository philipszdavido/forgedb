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

class Rabbit {
public:
    Rabbit(unordered_map<string, Table>& db) : db(db) {};
    void run();
private:
    int pc = 0;
    bool running = true;
    vector<Value> stack;
    Chunk* chunk;
    Table table;
    unordered_map<string, Table>& db;
};

#endif /* vm_hpp */
