//
//  main.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 13/04/2026.
//

#include <iostream>
#include <string>
#include "./parser/parser.hpp"
#include "./lexer/lexer.hpp"
#include "./token/Token.hpp"

int main(int argc, const char * argv[]) {
    
    const string sql = R"(
SELECT * FROM table
)";
    
    Lexer _lex(sql);
    vector<Token> tokens = _lex.lex();
    
    for (int i = 0; i < tokens.size(); i++) {
        printTokenType(tokens[i].type);
        std::cout << ' ' << tokens[i].value << std::endl;
    }
    
    return EXIT_SUCCESS;
}

