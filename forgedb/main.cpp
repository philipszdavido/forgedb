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
#include "plan-pipeline/plans/BasePlan/Plan.hpp"
#include "plan-pipeline/query/query.hpp"

Table users = {
    { {"id", "1"}, {"name", "Alice"}, {"age", "25"} },
    { {"id", "2"}, {"name", "Bob"},   {"age", "17"} },
    { {"id", "3"}, {"name", "Eve"},   {"age", "30"} }
};

unordered_map<string, Table> db = { { "users", users } };

int main(int argc, const char * argv[]) {
    
    const string sql = R"(
SELECT (SELECT * FROM table) FROM users
SELECT * FROM table
)";
    
    Lexer _lex(sql);
    vector<Token> tokens = _lex.lex();
    
    for (int i = 0; i < tokens.size(); i++) {
        printTokenType(tokens[i].type);
        std::cout << ' ' << tokens[i].value << std::endl;
    }
    
    Parser parser(tokens);
    parser.parse();

    vector<unique_ptr<Statement>> stmts = std::move(parser.stmts);
    
    for (int i = 0; i < stmts.size(); i++) {
        unique_ptr<Statement> stmt = std::move(stmts[i]);
        runStmtQuery(stmt.get(), db);
    }
    
    return EXIT_SUCCESS;
}

