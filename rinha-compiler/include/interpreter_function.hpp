#ifndef INTERPRETER_FUNCTION_HPP
#define INTERPRETER_FUNCTION_HPP
namespace rinha_compiler::walker {
    void load_paran_list(box<Function>&);
    void run_function_decl(box<Let>&);

}

#endif