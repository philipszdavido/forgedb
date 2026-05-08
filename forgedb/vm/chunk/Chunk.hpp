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

        if (std::holds_alternative<size_t>(data)) {
            return std::get<size_t>(data);
        }

        if (std::holds_alternative<std::string>(data)) {
            return std::stoull(std::get<std::string>(data));
        }

        if (std::holds_alternative<bool>(data)) {
            return std::get<bool>(data) ? 1 : 0;
        }

        throw std::runtime_error("Cannot convert to int");
    }

    std::string getStringValue() const {

        if (std::holds_alternative<std::string>(data)) {
            return std::get<std::string>(data);
        }

        if (std::holds_alternative<size_t>(data)) {
            return std::to_string(std::get<size_t>(data));
        }

        if (std::holds_alternative<bool>(data)) {
            return std::get<bool>(data) ? "true" : "false";
        }

        throw std::runtime_error("Cannot convert to string");
    }

    bool getBoolValue() const {

        if (std::holds_alternative<bool>(data)) {
            return std::get<bool>(data);
        }

        if (std::holds_alternative<size_t>(data)) {
            return std::get<size_t>(data) != 0;
        }

        if (std::holds_alternative<std::string>(data)) {
            return !std::get<std::string>(data).empty();
        }

        throw std::runtime_error("Cannot convert to bool");
    }
};

struct Chunk {
public:
    std::vector<uint8_t> code;
    std::vector<Value> constants;
};

#endif /* Chunk_hpp */
