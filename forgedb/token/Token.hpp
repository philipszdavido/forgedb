//
//  Token.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef Token_hpp
#define Token_hpp

#include <stdio.h>
#include <string>
#include "../TokenType/TokenType.hpp"

using namespace std;

class Token {
    
public:
    const TokenType type;
    const std::string value;
    
    Token(const TokenType type, const std::string value = "") : type(type), value(value) {}

};

#endif /* Token_hpp */
