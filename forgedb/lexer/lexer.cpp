//
//  lexer.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 14/04/2026.
//

#include "lexer.hpp"

unordered_map<string, string> keywords = {
    { "SELECT", "SELECT" },
    { "UPDATE", "UPDATE" },
    { "CREATE", "CREATE" },
    { "DELETE", "DELETE" },
    { "FROM", "FROM" },
    
    {"LIMIT", "LIMIT"},
    {"OFFSET", "OFFSET"},
    {"WHERE", "WHERE"}
};

Lexer::Lexer(const std::string& sql) : sql(sql) {}

vector<Token> Lexer::lex() {
    
    while (!eof()) {
        const char c = current();
        
        switch (c) {
            case '=':
                add(TokenType::EQUALS, c);
                break;
                
            case '<':
                add(TokenType::LT, c);
                break;
                
            case '>':
                add(TokenType::GT, c);
                break;
                
            case '*':
                add(TokenType::STAR, c);
                break;
                
            case '(':
                add(TokenType::LEFT_PAREN, c);
                break;
                
            case ')':
                add(TokenType::RIGHT_PAREN, c);
                break;
                
            case ',':
                add(TokenType::COMMA, c);
                break;
                
            default:
                
                if (isAlpha(c)) {
                    collectIdentifier();
                } else if (isDigit(c)) {
                    collectDigit();
                }
                
                break;
        }
        
        advance();
        
    }
    
    return tokens;
    
}

void Lexer::collectIdentifier() {
    string ident = "";
    ident += current();
    
    advance();
    
    while (!eof() && isAlpha(current())) {
        ident += current();
        advance();
    }
    
    const string kw = keywords[ident];
    if (kw.size()) {
        add(TokenType::KEYWORD, ident);
    } else add(TokenType::STRING, ident);
    index--;
    
}

void Lexer::collectDigit() {
    
    string ident = "";
    ident += current();
    
    advance();
    
    while (!eof() && isDigit(current())) {
        ident += current();
        advance();
    }
    
    add(TokenType::NUMBER, ident);
    
    index--;

}

char Lexer::current() { return eof() ? '\0' : sql[index]; }
char Lexer::next(int o) { return (index + o < sql.size()) ? sql[index + o] : '\0'; }
void Lexer::advance() { index++; }
bool Lexer::eof() { return index >= sql.size(); }

bool Lexer::isWhitespace(char c) { return isspace(c); }
bool Lexer::isDigit(char c) { return isdigit(c); }
bool Lexer::isAlpha(char c) { return isalpha(c); }

void Lexer::add(TokenType type, const char value) {
    string v = "";
    v += value;
    add(type, v);
}

void Lexer::add(TokenType type, string value) {
    tokens.emplace_back(type, value);
}
