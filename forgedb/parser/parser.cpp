//
//  parser.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 14/04/2026.
//

#include "parser.hpp"

void Parser::parse() {
    while (!eof()) {
        Token token = current();
        
        if (token.type == TokenType::KEYWORD) {
            if (token.value == "SELECT") {
                auto select = parseSelect();
                stmts.push_back(std::move(select));
            }
        }
        
        advance();
    }
}

unique_ptr<Select> Parser::parseSelect() {
    unique_ptr<Select> select = make_unique<Select>();
    
    consumeToken(current(), "Expected SELECT");
    
    // next is columns
    
    if (current().type == TokenType::STAR) {
        
        select->column.isStar = true;
        
    } else if (current().type == TokenType::LEFT_PAREN) {
        
        // collect till )
        unique_ptr<Select> childSelect;
        while (current().type != TokenType::RIGHT_PAREN) {
            childSelect = parseSelect();
        }
        
        select->column.isSelect = true;
        select->column.selectColmun = std::move(childSelect);
        
    } else {
        
        vector<string> cols;
        // consume all comma
        cols.push_back(current().value); advance();
        
        while (current().type == TokenType::COMMA) {
            advance();
            cols.push_back(current().value); advance();
        }
        select->column.isStar = false;
        select->column.columns = cols;
    }
    
    if (current().type == TokenType::KEYWORD && current().value == "FROM") {
        
        // pick the table
        consumeToken(current(), "Expected 'FROM'");
        select->table = current().value;
        
    }
    
    // pick WHERE
    if (current().type == TokenType::KEYWORD && current().value == "WHERE") {
        advance();
        
        auto where = make_unique<Where>();
        
        // consume till hit a keyword
        while (true) {
            if (current().type == TokenType::KEYWORD || eof()) {
                break;
            }
        }
        
    }
    
    return select;
    
}

void Parser::consumeToken(Token token, string msgError) {
    if (current().type == token.type && current().value == token.value && !eof()) {
        return advance();
    }
    throw runtime_error(msgError);
}

void Parser::consumeTokenType(TokenType type, string msgError) {
    if (current().type == type && !eof()) {
        return advance();
    }
    throw runtime_error(msgError);
}

Token Parser::current() { return tokens[index]; }
Token Parser::next() { return tokens[index + 1]; }

void Parser::advance() { index++; }

bool Parser::eof() {
    return index >= tokens.size() || tokens[index].type == TokenType::END_OF_FILE;
}

bool Parser::match(TokenType type) {
    if (current().type != type) return false;

    advance();
    return true;

}
