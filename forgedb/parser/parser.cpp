//
//  parser.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 14/04/2026.
//

#include "parser.hpp"

using namespace std;

void Parser::parse() {

    while (!eof()) {

        auto stmt = parseStatement();

        stmts.push_back(std::move(stmt));

        // ;
        match(TokenType::SEMICOLON);
    }
}

unique_ptr<Statement> Parser::parseStatement() {

    if (checkKeyword("SELECT")) {
        return parseSelect();
    }

    throw runtime_error(
        "Unknown statement: " + current().value
    );
}

unique_ptr<Select> Parser::parseSelect() {

    unique_ptr<Select> select = make_unique<Select>();

    consumeKeyword("SELECT");

    parseSelectList(*select);

    parseFrom(*select);

    parseJoins(*select);

    parseWhere(*select);

    parseGroupBy(*select);

    parseHaving(*select);

    parseOrderBy(*select);

    parseLimit(*select);

    parseOffset(*select);

    return select;
}

void Parser::parseSelectList(Select& select) {

    while (true) {

        SelectItem item;

        item.expr = parseExpression();

        // chop alias
        if (checkKeyword("AS")) {

            advance();

            if (current().type != TokenType::IDENT) {
                throw runtime_error("Expected alias");
            }

            item.alias = current().value;

            advance();

        } else if (current().type == TokenType::IDENT) {

            // implicit alias:
            // SELECT age years
            item.alias = current().value;

            advance();
        }

        select.columns.push_back(std::move(item));

        if (!match(TokenType::COMMA))
            break;
    }
}

void Parser::parseFrom(Select& select) {

    if (!checkKeyword("FROM"))
        return;

    consumeKeyword("FROM");

    TableRef table;

    // subquery
    if (match(TokenType::LEFT_PAREN)) {

        table.type = TableType::SUBQUERY;

        auto stmt = parseSelect();

        table.subquery.reset(
            static_cast<Select*>(stmt.release())
        );

        consumeTokenType(
            TokenType::RIGHT_PAREN,
            "Expected ')'"
        );

    } else {

        // normal table
        consumeTokenType(
            TokenType::IDENT,
            "Expected table name"
        );

        table.type = TableType::TABLE;
        table.name = tokens[index - 1].value;
    }

    // alias
    if (current().type == TokenType::IDENT) {

        table.alias = current().value;

        advance();
    }

    select.from = std::move(table);
}

void Parser::parseJoins(Select& select) {

    while (true) {

        Join join;

        // INNER JOIN
        if (checkKeyword("INNER")) {

            advance();

            consumeKeyword("JOIN");

            join.type = JoinType::INNER;
        }

        // LEFT JOIN
        else if (checkKeyword("LEFT")) {

            advance();

            consumeKeyword("JOIN");

            join.type = JoinType::LEFT;
        }

        // RIGHT JOIN
        else if (checkKeyword("RIGHT")) {

            advance();

            consumeKeyword("JOIN");

            join.type = JoinType::RIGHT;
        }

        // FULL JOIN
        else if (checkKeyword("FULL")) {

            advance();

            consumeKeyword("JOIN");

            join.type = JoinType::FULL;
        }

        // JOIN
        else if (checkKeyword("JOIN")) {

            advance();

            join.type = JoinType::INNER;
        }

        else {
            break;
        }

        // table
        consumeTokenType(
            TokenType::IDENT,
            "Expected table name"
        );

        join.table.type = TableType::TABLE;
        join.table.name = tokens[index - 1].value;

        // alias
        if (current().type == TokenType::IDENT) {

            join.table.alias = current().value;

            advance();
        }

        consumeKeyword("ON");

        join.on = parseExpression();

        select.joins.push_back(std::move(join));
    }
}

void Parser::parseWhere(Select& select) {

    if (!checkKeyword("WHERE"))
        return;

    consumeKeyword("WHERE");

    select.where = parseExpression();
}

void Parser::parseGroupBy(Select& select) {

    if (!checkKeyword("GROUP"))
        return;

    consumeKeyword("GROUP");

    consumeKeyword("BY");

    while (true) {

        select.groupBy.push_back(
            parseExpression()
        );

        if (!match(TokenType::COMMA))
            break;
    }
}

void Parser::parseHaving(Select& select) {

    if (!checkKeyword("HAVING"))
        return;

    consumeKeyword("HAVING");

    select.having = parseExpression();
}

void Parser::parseOrderBy(Select& select) {

    if (!checkKeyword("ORDER"))
        return;

    consumeKeyword("ORDER");

    consumeKeyword("BY");

    while (true) {

        OrderItem item;

        item.expr = parseExpression();

        if (checkKeyword("DESC")) {

            advance();

            item.direction = OrderDirection::DESC;

        } else {

            matchKeyword("ASC");

            item.direction = OrderDirection::ASC;
        }

        select.orderBy.push_back(std::move(item));

        if (!match(TokenType::COMMA))
            break;
    }
}

void Parser::parseLimit(Select& select) {

    if (!checkKeyword("LIMIT"))
        return;

    consumeKeyword("LIMIT");

    consumeTokenType(
        TokenType::NUMBER,
        "Expected limit number"
    );

    select.limit = stoi(tokens[index - 1].value);
}

void Parser::parseOffset(Select& select) {

    if (!checkKeyword("OFFSET"))
        return;

    consumeKeyword("OFFSET");

    consumeTokenType(
        TokenType::NUMBER,
        "Expected offset number"
    );

    select.offset = stoi(tokens[index - 1].value);
}

unique_ptr<Expression> Parser::parseExpression() {
    return parseOr();
}

unique_ptr<Expression> Parser::parseOr() {

    auto left = parseAnd();

    while (checkKeyword("OR")) {

        advance();

        auto right = parseAnd();

        auto expr = make_unique<BinaryExpression>();

        expr->op = BinaryOp::OR;
        expr->left = std::move(left);
        expr->right = std::move(right);

        left = std::move(expr);
    }

    return left;
}

unique_ptr<Expression> Parser::parseAnd() {

    auto left = parseEquality();

    while (checkKeyword("AND")) {

        advance();

        auto right = parseEquality();

        auto expr = make_unique<BinaryExpression>();

        expr->op = BinaryOp::AND;
        expr->left = std::move(left);
        expr->right = std::move(right);

        left = std::move(expr);
    }

    return left;
}

unique_ptr<Expression> Parser::parseEquality() {

    auto left = parseComparison();

    while (
        check("=") ||
        check("==") ||
        check("!=")
    ) {

        Token op = current();

        advance();

        auto right = parseComparison();

        auto expr = make_unique<BinaryExpression>();

        expr->left = std::move(left);
        expr->right = std::move(right);

        if (op.value == "=" || op.value == "==")
            expr->op = BinaryOp::EQ;
        else
            expr->op = BinaryOp::NEQ;

        left = std::move(expr);
    }

    return left;
}

unique_ptr<Expression> Parser::parseComparison() {

    auto left = parseTerm();

    while (
        check(">") ||
        check(">=") ||
        check("<") ||
        check("<=")
    ) {

        Token op = current();

        advance();

        auto right = parseTerm();

        auto expr = make_unique<BinaryExpression>();

        expr->left = std::move(left);
        expr->right = std::move(right);

        if (op.value == ">")
            expr->op = BinaryOp::GT;
        else if (op.value == ">=")
            expr->op = BinaryOp::GTE;
        else if (op.value == "<")
            expr->op = BinaryOp::LT;
        else
            expr->op = BinaryOp::LTE;

        left = std::move(expr);
    }

    return left;
}

unique_ptr<Expression> Parser::parseTerm() {

    auto left = parseFactor();

    while (
        check("+") ||
        check("-")
    ) {

        Token op = current();

        advance();

        auto right = parseFactor();

        auto expr = make_unique<BinaryExpression>();

        expr->left = std::move(left);
        expr->right = std::move(right);

        expr->op =
            op.value == "+"
            ? BinaryOp::ADD
            : BinaryOp::SUB;

        left = std::move(expr);
    }

    return left;
}

unique_ptr<Expression> Parser::parseFactor() {

    auto left = parseUnary();

    while (
        check("*") ||
        check("/")
    ) {

        Token op = current();

        advance();

        auto right = parseUnary();

        auto expr = make_unique<BinaryExpression>();

        expr->left = std::move(left);
        expr->right = std::move(right);

        expr->op =
            op.value == "*"
            ? BinaryOp::MUL
            : BinaryOp::DIV;

        left = std::move(expr);
    }

    return left;
}

unique_ptr<Expression> Parser::parseUnary() {

    if (checkKeyword("NOT")) {

        advance();

        auto expr = make_unique<UnaryExpression>();

        expr->op = UnaryOp::NOT;
        expr->expr = parseUnary();

        return expr;
    }

    if (check("-")) {

        advance();

        auto expr = make_unique<UnaryExpression>();

        expr->op = UnaryOp::NEGATE;
        expr->expr = parseUnary();

        return expr;
    }

    return parsePrimary();
}

unique_ptr<Expression> Parser::parsePrimary() {

    if (match(TokenType::LEFT_PAREN)) {

        auto expr = parseExpression();

        consumeTokenType(
            TokenType::RIGHT_PAREN,
            "Expected ')'"
        );

        return expr;
    }

    if (match(TokenType::STAR)) {
        return make_unique<StarExpression>();
    }

    if (current().type == TokenType::NUMBER) {

        auto expr = make_unique<Literal>();

        expr->value = current().value;

        advance();

        return expr;
    }

    if (current().type == TokenType::STRING) {

        auto expr = make_unique<Literal>();

        expr->value = current().value;

        advance();

        return expr;
    }

    if (current().type == TokenType::IDENT) {

        string name = current().value;

        advance();

        if (match(TokenType::LEFT_PAREN)) {

            auto func = make_unique<FunctionExpression>();

            func->name = name;

            if (!match(TokenType::RIGHT_PAREN)) {

                while (true) {

                    func->args.push_back(
                        parseExpression()
                    );

                    if (match(TokenType::RIGHT_PAREN))
                        break;

                    consumeTokenType(
                        TokenType::COMMA,
                        "Expected ','"
                    );
                }
            }

            return func;
        }

        auto col = make_unique<ColumnExpression>();

        col->name = name;

        return col;
    }

    throw runtime_error(
        "Unexpected token: " + current().value
    );
}

bool Parser::eof() {

    return
        index >= tokens.size() ||
        tokens[index].type == TokenType::END_OF_FILE;
}

Token Parser::current() {
    return tokens[index];
}

Token Parser::next() {
    return tokens[index + 1];
}

void Parser::advance() {
    index++;
}

bool Parser::match(TokenType type) {

    if (eof())
        return false;

    if (current().type != type)
        return false;

    advance();

    return true;
}

bool Parser::check(string value) {

    if (eof())
        return false;

    return current().value == value;
}

bool Parser::checkKeyword(string keyword) {

    if (eof())
        return false;

    return
        current().type == TokenType::KEYWORD &&
        current().value == keyword;
}

bool Parser::matchKeyword(string keyword) {

    if (!checkKeyword(keyword))
        return false;

    advance();

    return true;
}

void Parser::consumeKeyword(string keyword) {

    if (!checkKeyword(keyword)) {

        throw runtime_error(
            "Expected keyword: " + keyword
        );
    }

    advance();
}

void Parser::consumeTokenType(
    TokenType type,
    string error
) {

    if (eof() || current().type != type) {
        throw runtime_error(error);
    }

    advance();
}
