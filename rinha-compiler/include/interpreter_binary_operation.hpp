#include <interpreter.hpp>

#ifndef INTERPRETER_BINARY_OPERATION_HPP
#define INTERPRETER_BINARY_OPERATION_HPP

namespace rinha_compiler::interpreter {
    void bin_op(box<Binary>&);
    void run_plus(box<Binary>&);
    void run_minus(box<Binary>&);
    void run_times(box<Binary>&);
    void run_over(box<Binary>&);
    void run_rem(box<Binary>&);
    void run_eq(box<Binary>&);
    void run_neq(box<Binary>&);
    void run_lt(box<Binary>&);
    void run_gt(box<Binary>&);
    void run_lte(box<Binary>&);
    void run_gte(box<Binary>&);
    void run_and(box<Binary>&);
    void run_or(box<Binary>&);

}
#endif