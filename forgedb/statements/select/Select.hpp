//
//  Select.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef Select_hpp
#define Select_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>

#include "statements/statement/Statement.hpp"
#include "statements/where/Where.hpp"
#include "expressions/Expression/Expression.hpp"

using namespace std;

// Execution order:
// FROM
// WHERE (filter rows)
// GROUP BY (create groups)
// HAVING (filter groups)
// SELECT

// SELECT customer, SUM(amount)
// FROM orders
// GROUP BY customer
// HAVING SUM(amount) > 50;

class Statement;
class Select;

class StarExpression : public Expression {
public:

    StarExpression() {}
    std::string toString() const {
        return "()";
    }

};

class ColumnExpression : public Expression {
public:

    string table;
    string name;
    string alias;
    
    ColumnExpression() {}
    std::string toString() const {
        return "()";
    }

};

class FunctionExpression : public Expression {
public:

    string name;
    vector<unique_ptr<Expression>> args;
    bool distinct = false;
    
    FunctionExpression() {}
    
    std::string toString() const {
        return "()";
    }

};

enum class UnaryOp {
    NOT,
    NEGATE
};

class UnaryExpression : public Expression {
public:
    UnaryOp op;
    unique_ptr<Expression> expr;
    
    UnaryExpression() {}
    std::string toString() const {
        return "()";
    }

};

struct SelectItem {
    unique_ptr<Expression> expr;
    string alias;
};

enum class TableType {
    TABLE,
    SUBQUERY
};

struct TableRef {
    TableType type = TableType::TABLE;

    string name;
    string alias;

    unique_ptr<Select> subquery;
};

enum class JoinType {
    INNER,
    LEFT,
    RIGHT,
    FULL,
    CROSS
};

struct Join {
    JoinType type;

    TableRef table;

    unique_ptr<Expression> on;
};

enum class OrderDirection {
    ASC,
    DESC
};

struct OrderItem {
    unique_ptr<Expression> expr;
    OrderDirection direction = OrderDirection::ASC;
};

class Select : public Statement {
public:

    vector<SelectItem> columns;

    TableRef from;

    vector<Join> joins;

    unique_ptr<Expression> where;

    vector<unique_ptr<Expression>> groupBy;

    unique_ptr<Expression> having;

    vector<OrderItem> orderBy;

    int limit = -1;
    int offset = -1;

public:
    Select() = default;

    Select(Select&&) = default;
    Select& operator=(Select&&) = default;

    Select(const Select&) = delete;
    Select& operator=(const Select&) = delete;
};

#endif /* Select_hpp */
