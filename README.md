# ForgeDB

A lightweight SQL-inspired database engine written in modern C++.

ForgeDB explores how real database systems work internally by implementing:

* SQL-style query execution
* Bytecode virtual machines
* Table scanning
* Query planning
* Execution pipelines
* Low-level database internals

The project is designed both as a learning resource and an experimental database runtime.

---

# Features

* SQL-like execution model
* Custom bytecode VM
* Stack-based execution engine
* Table storage in memory
* Row iteration and cursors
* Query instructions (`OpenRead`, `Column`, `ResultRow`, `Next`, etc.)
* WHERE filtering
* GROUP BY support
* HAVING support
* Indirect-threaded VM experiments
* Extensible opcode architecture
* Modern C++ implementation

---

# Example Query Flow

A query like:

```sql
SELECT name FROM users;
```

Can compile into VM bytecode like:

```cpp
[
  SetTable "users",
  SetCurrentRow,
  SelectColumn name,
  IncrementRowIndex,
  Jump,
  Halt
]
```

The VM then executes instructions sequentially.

---

# Architecture

ForgeDB is inspired by the internal architecture of systems like:

* [SQLite](https://www.sqlite.org/index.html?utm_source=chatgpt.com)
* [DuckDB](https://duckdb.org/?utm_source=chatgpt.com)
* [PostgreSQL](https://www.postgresql.org/?utm_source=chatgpt.com)
* [V8 Engine](https://v8.dev/?utm_source=chatgpt.com)

Core layers:

```text
SQL
 ↓
Parser
 ↓
Planner
 ↓
Bytecode Compiler
 ↓
Virtual Machine
 ↓
Execution Engine
 ↓
Storage
```

---

# Example VM Instructions

| Opcode      | Description              |
| ----------- | ------------------------ |
| `OpenRead`  | Open a table             |
| `Rewind`    | Move cursor to first row |
| `Column`    | Read a column value      |
| `Push`      | Push constant onto stack |
| `Eq`        | Equality comparison      |
| `Jump`      | Jump instruction pointer |
| `ResultRow` | Emit row                 |
| `Next`      | Move to next row         |
| `Halt`      | Stop execution           |

---

# Project Structure

```text
forgedb/
├── src/
│   ├── vm/
│   ├── parser/
│   ├── planner/
│   ├── compiler/
│   ├── storage/
│   └── execution/
│
├── include/
├── tests/
├── examples/
└── README.md
```

---

# Building

## Requirements

* C++20 compiler
* CMake
* Xcode / Clang / GCC

## Build

```bash
git clone https://github.com/philipszdavido/forgedb.git

cd forgedb

mkdir build
cd build

cmake ..
make
```

---

# Running

```bash
./forgedb
```

---

# Example

```cpp
unordered_map<string, Table> db;

db["users"] = {
    {
        {"id", "1"},
        {"name", "Alice"},
        {"age", "25"}
    },
    {
        {"id", "2"},
        {"name", "Bob"},
        {"age", "30"}
    }
};
```

---

# Goals

ForgeDB aims to evolve into:

* Vectorized execution engine
* Query optimizer
* Cost-based planner
* Index support
* Join algorithms
* Disk-backed storage
* Transactions
* MVCC
* JIT compilation
* Parallel execution
* Distributed query processing

---

# Learning Objectives

This project helps developers understand:

* How databases execute queries
* How SQL compilers work
* Virtual machine design
* Query optimization
* Bytecode execution
* Memory layouts
* Database storage engines
* Vectorized processing
* Systems programming in C++

---

# Roadmap

## Current

* [x] Basic VM
* [x] Table scanning
* [x] Result rows
* [x] WHERE execution
* [x] Stack machine
* [x] Indirect threading experiments

## In Progress

* [ ] SQL parser
* [ ] Query planner
* [ ] Bytecode compiler
* [ ] GROUP BY aggregation
* [ ] JOIN support

## Future

* [ ] Disk storage
* [ ] B-Tree indexes
* [ ] Transactions
* [ ] MVCC
* [ ] WAL
* [ ] Cost-based optimizer
* [ ] SIMD/vectorized execution
* [ ] JIT compiler

---

# Inspiration

ForgeDB is heavily inspired by studying:

* SQLite VM internals
* PostgreSQL execution engine
* DuckDB vectorized execution
* V8 interpreter architecture
* Database systems research papers

---

# Contributing

Contributions are welcome.

Ideas:

* Add new VM instructions
* Improve parser
* Build optimizer passes
* Add storage formats
* Implement indexes
* Improve execution performance

---

# License

MIT License

---

# Author

Built by Chidume Nnamdi

* GitHub: [philipszdavido](https://github.com/philipszdavido?utm_source=chatgpt.com)
