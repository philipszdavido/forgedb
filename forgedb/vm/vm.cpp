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

#define BINARY_COMPARE(op) \
{ \
    Value rhs = pop(); \
    Value lhs = pop(); \
    push(Value(lhs.getIntValue() op rhs.getIntValue())); \
    break; \
}

#define BINARY_LOGIC(op) \
{ \
    Value rhs = pop(); \
    Value lhs = pop(); \
    push(Value(lhs.getBoolValue() op rhs.getBoolValue())); \
    break; \
}

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
                
                Value v = chunk->constants[chunk->code[pc++]];
                stack.push_back(v);
                
                break;
            }
                
            case OpCode::SelectAllColumns: {
                tempTable.push_back(*currentRow);
                break;
            }
                
            case OpCode::SelectColumn: {
                Row projected;
                
                for (Value col : stack) {
                    
                    std::string columnName = col.getStringValue();
                    
                    projected[columnName] =
                    (*currentRow)[columnName];
                }
                
                tempTable.push_back(projected);
                
                stack.clear();
                break;
            }
                
            case OpCode::SetRowToTempTable: {
                tempTable.push_back(*currentRow);
                break;
            }
                
            case OpCode::SetCurrentRow: {
                currentRow = &(*table)[rowIndex];
                break;
            }
                
            case OpCode::IncrementRowIndex: {
                rowIndex++;
                break;
            }
                
                // Conditionals
            case OpCode::GreaterThan: {
                
                BINARY_COMPARE(>);
                
                break;
            }
                
            case OpCode::LessThan: {
                
                BINARY_COMPARE(<);

                break;
            }
                
            case OpCode::GreaterThanOrEqual: {
                
                BINARY_COMPARE(>=);
                
                break;
            }
                
            case OpCode::LessThanOrEqual: {
                
                BINARY_COMPARE(<=);

                break;
            }
                
            case OpCode::Or: {
                
                BINARY_LOGIC(||);

                break;
            }
                
            case OpCode::And: {
                
                BINARY_LOGIC(&&);

                break;
            }
                
            case OpCode::Equal: {
                
                BINARY_COMPARE(==);

                break;
            }
                
            case OpCode::NotEqual: {
                
                BINARY_COMPARE(!=);

                break;
            }
                
            case OpCode::GetColumnValue: {
                
                Value x = pop();
                Value v = (*currentRow)[x.getStringValue()];
                push(v);
                
                break;
            }
                
            case OpCode::JumpIfFalse: {
                // We pop from stack and check the result
                Value x = pop();
                
                if (x.getBoolValue()) {
                    Value label = chunk->constants[chunk->code[pc++]];
                    pc = (int)label.getIntValue();
                }
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

void Rabbit::push(Value x) {
    stack.push_back(x);
}

Value Rabbit::pop() {
    
    if (stack.empty()) {
        throw runtime_error("Empty stack.");
    }
    
    Value x = stack.back();
    stack.pop_back();
    return x;
}

void Rabbit::setChunk(const Chunk* c) {
    chunk = c;
}
