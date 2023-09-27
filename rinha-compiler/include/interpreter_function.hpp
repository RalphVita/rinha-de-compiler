#include <box.hpp>
#include <ast.hpp>
#include <function_cache.hpp>
#ifndef INTERPRETER_FUNCTION_HPP
#define INTERPRETER_FUNCTION_HPP

namespace rinha_compiler::walker {
    void load_param_list_in_memory(box<Function>&);
    void run_function_decl(box<Let>&);

}

#endif