#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.hpp"
#include <stack.hpp>
#include <memory.hpp>
#include <symbol_table.hpp>

extern rinha_compiler::stack _stack;
extern rinha_compiler::Memory _memory;
extern rinha_compiler::SymbolTable* symbolTable;
extern int current_scope;

namespace rinha_compiler::interpreter {
    void walk(File file);
}

#endif
