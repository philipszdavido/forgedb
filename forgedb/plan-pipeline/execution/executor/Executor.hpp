//
//  Executor.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 26/04/2026.
//

#ifndef Executor_hpp
#define Executor_hpp

#include <stdio.h>
#include <unordered_map>

#include "plan-pipeline/plans/BasePlan/Plan.hpp"

using namespace std;

struct Executor {
    virtual ~Executor() = default;
    virtual bool next(Row& out) = 0;
};

struct ScanExecutor : Executor {
    Table& table;
    size_t index = 0;

    ScanExecutor(Table& t) : table(t) {}

    bool next(Row& out) override {
        if (index >= table.size()) return false;
        out = table[index++];
        return true;
    }
};

bool eval(Expression* expr, const Row& row);

struct FilterExecutor : Executor {
    unique_ptr<Executor> input;
    unique_ptr<Expression> predicate;

    FilterExecutor(unique_ptr<Executor> in,
                   unique_ptr<Expression> pred)
        : input(std::move(in)), predicate(std::move(pred)) {}

    bool next(Row& out) override {
        while (input->next(out)) {
            if (eval(predicate.get(), out)) {
                return true;
            }
        }
        return false;
    }
};

struct StarColumnProjectionExecutor : Executor {
    unique_ptr<Executor> input;

    StarColumnProjectionExecutor(unique_ptr<Executor> in)
        : input(std::move(in)) {}

    bool next(Row& out) override {
        Row projected;
        if (!input->next(projected)) return false;

        out = projected;
        return true;
    }
};

struct SelectColumnProjectionExecutor : Executor {
    unique_ptr<Executor> input;

    SelectColumnProjectionExecutor(unique_ptr<Executor> in,
                       vector<string> cols)
        : input(std::move(in)) {}

    bool next(Row& out) override {
        Row temp;
        if (!input->next(temp)) return false;

        out = temp;
        return true;
    }
};

struct ProjectionExecutor : Executor {
    unique_ptr<Executor> input;
    vector<string> columns;

    ProjectionExecutor(unique_ptr<Executor> in,
                       vector<string> cols)
        : input(std::move(in)), columns(std::move(cols)) {}

    bool next(Row& out) override {
        Row temp;
        if (!input->next(temp)) return false;

        Row projected;
        for (auto& col : columns) {
            projected[col] = temp[col];
        }

        out = projected;
        return true;
    }
};

struct LimitExecutor : Executor {
    unique_ptr<Executor> input;
    int remaining;

    LimitExecutor(unique_ptr<Executor> in, int l)
        : input(std::move(in)), remaining(l) {}

    bool next(Row& out) override {
        if (remaining <= 0) return false;
        if (!input->next(out)) return false;

        remaining--;
        return true;
    }
};

unique_ptr<Executor> buildExecutor(Plan* plan, unordered_map<string, Table>& db);

#endif /* Executor_hpp */
