cmake_minimum_required(VERSION 3.20)
project(forgedb VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(FORGEDB_BUILD_TESTS "Build tests" ON)

# Library
add_library(forgedb)

# Sources
target_sources(forgedb
    PRIVATE
        src/expressions/where/Condition.cpp
        src/statement/Select.cpp
)

# Include paths
target_include_directories(forgedb
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Warnings (modular)
include(cmake/warnings.cmake)
set_project_warnings(forgedb)

# CLI app
add_executable(forgedb_cli
    apps/cli/main.cpp
)

target_link_libraries(forgedb_cli PRIVATE forgedb)

# Tests
if(FORGEDB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()