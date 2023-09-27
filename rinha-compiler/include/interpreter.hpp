#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.hpp"
#include <stack.hpp>
#include <memory.hpp>
#include <symbol_table.hpp>
#include <function_cache.hpp>

extern rinha_compiler::stack _stack;
extern rinha_compiler::Memory _memory;
extern rinha_compiler::SymbolTable* symbolTable;
extern int current_scope;
//extern rinha_compiler::FunctionCache function_cache;

namespace rinha_compiler::interpreter {
    void walk(File file);
}

#endif
