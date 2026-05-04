//
//  Chunk.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 03/05/2026.
//

#ifndef Chunk_hpp
#define Chunk_hpp

#include <stdio.h>
#include <vector>
#include <variant>

struct Value {
    std::variant<size_t, std::string, bool> data;

    Value(size_t v) : data(v) {}
    Value(const std::string& v) : data(v) {}
    Value(bool v) : data(v) {}

    size_t getIntValue() const {
        return std::get<size_t>(data);
    }

    std::string getStringValue() const {
        return std::get<std::string>(data);
    }

    bool getBoolValue() const {
        return std::get<bool>(data);
    }
};

struct Chunk {
    std::vector<uint8_t> code;
    std::vector<Value> constant;
};

#endif /* Chunk_hpp */
