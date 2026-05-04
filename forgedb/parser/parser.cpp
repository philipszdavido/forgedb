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
    select->limit = -1;
    
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
    
    advance();
    
    if (current().type == TokenType::KEYWORD && current().value == "FROM") {
        
        // pick the table
        consumeToken(current(), "Expected 'FROM'");
        select->table = current().value;
        advance();
    }
    
    // pick WHERE
    if (current().type == TokenType::KEYWORD && current().value == "WHERE") {
        advance();
        
        auto where = make_unique<Where>();
        
        // consume till we hit a keyword
        while (true) {
            if (current().type == TokenType::KEYWORD || eof()) {
                break;
            }
            unique_ptr<Expression> expr = parseExpression();
            where->expression = std::move(expr);
            break;
        }
        select->where = std::move(where);
    }
    
    return select;
    
}

unique_ptr<Expression> Parser::parseExpression() {
    
    return parseOr();
    
}

unique_ptr<Expression> Parser::parseBinary() {
    
    auto left = parsePrimary();
        
    while(checkValues({">", ">=", "<", "<=", "==", "!=", "AND", "OR"})) {
        Token token = tokens[index - 1];
        auto expr = parsePrimary();
        left = make_unique<BinaryExpression>(std::move(left), toBinaryOp(token.value), std::move(expr));
    }
    
    return left;

}

unique_ptr<Expression> Parser::parseOr() {
    auto left = parseAnd();

    while (checkValues({"OR"})) {
        auto right = parseAnd();

        left = make_unique<BinaryExpression>(
            std::move(left),
            BinaryOp::OR,
            std::move(right)
        );
    }

    return left;
}

unique_ptr<Expression> Parser::parseAnd() {
    auto left = parseComparison();

    while (checkValues({"AND"})) {
        auto right = parseComparison();

        left = make_unique<BinaryExpression>(
            std::move(left),
            BinaryOp::AND,
            std::move(right)
        );
    }

    return left;
}

unique_ptr<Expression> Parser::parseComparison() {
    auto left = parsePrimary();

    while (checkValues({">", ">=", "<", "<=", "==", "!="})) {
        Token token = tokens[index - 1];

        auto right = parsePrimary();

        left = make_unique<BinaryExpression>(
            std::move(left),
            toBinaryOp(token.value),
            std::move(right)
        );
    }

    return left;
}

unique_ptr<Expression> Parser::parsePrimary() {
    
    Token token = current();
    
    if (token.type == TokenType::STRING) {
        advance();
        return make_unique<Literal>(token.value);
    }
    
    if (token.type == TokenType::NUMBER) {
        advance();
        return make_unique<Literal>(token.value);
    }
    
    if (token.type == TokenType::IDENT) {
        advance();
        return make_unique<Identifier>(token.value);
    }
    
    throw runtime_error("Unknown op.");
}

bool Parser::checkValues(std::initializer_list<string> values) {
    for (auto t : values) {
        if (check(t)) {
            advance();
            return true;
        }
    }
    return false;
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

bool Parser::check(std::string type) {
    if (eof()) return false;
    return current().value == type;
}
