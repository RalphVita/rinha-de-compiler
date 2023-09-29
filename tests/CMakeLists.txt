cmake_minimum_required(VERSION 3.0)

###############################
# parser_json_to_ast_test.cpp #
###############################
add_executable(parser_json_to_ast_test src/parser_json_to_ast_test.cpp )
target_include_directories(parser_json_to_ast_test PUBLIC "${CMAKE_SOURCE_DIR}/rinha-compiler")
target_link_libraries(parser_json_to_ast_test PUBLIC rinha-compiler )


add_test(NAME test_parser_json_print COMMAND parser_json_to_ast_test "test_parser_json_print" "${CMAKE_SOURCE_DIR}/tests/test_data/print.json")
add_test(NAME test_parser_json_sum COMMAND parser_json_to_ast_test "test_parser_json_sum" "${CMAKE_SOURCE_DIR}/tests/test_data/sum.json")
add_test(NAME test_parser_json_fib COMMAND parser_json_to_ast_test "test_parser_json_fib" "${CMAKE_SOURCE_DIR}/tests/test_data/fib.json")

###################
# Interpreter.cpp #
###################
add_executable(interpreter_test src/interpreter_test.cpp )
target_include_directories(interpreter_test PUBLIC "${CMAKE_SOURCE_DIR}/rinha-compiler")
target_link_libraries(interpreter_test PUBLIC rinha-compiler )

add_test(NAME test_let_bool COMMAND interpreter_test "test_let_bool" "${CMAKE_SOURCE_DIR}/tests/test_data/let_bool.json")
add_test(NAME test_let_int COMMAND interpreter_test "test_let_int" "${CMAKE_SOURCE_DIR}/tests/test_data/let_int.json")
add_test(NAME test_let_str COMMAND interpreter_test "test_let_str" "${CMAKE_SOURCE_DIR}/tests/test_data/let_str.json")
add_test(NAME test_let_tuple COMMAND interpreter_test "test_let_tuple" "${CMAKE_SOURCE_DIR}/tests/test_data/let_tuple.json")
add_test(NAME test_first_second COMMAND interpreter_test "test_first_second" "${CMAKE_SOURCE_DIR}/tests/test_data/first_second.json")
add_test(NAME test_if COMMAND interpreter_test "test_if" "${CMAKE_SOURCE_DIR}/tests/test_data/if.json")
add_test(NAME test_else COMMAND interpreter_test "test_else" "${CMAKE_SOURCE_DIR}/tests/test_data/else.json")

add_test(NAME test_sum_print COMMAND interpreter_test "test_sum_print" "${CMAKE_SOURCE_DIR}/tests/test_data/sum_print.json")
add_test(NAME test_nested_print COMMAND interpreter_test "test_nested_print" "${CMAKE_SOURCE_DIR}/tests/test_data/nested_print.json")
add_test(NAME test_nested_print_tuple COMMAND interpreter_test "test_nested_print_tuple" "${CMAKE_SOURCE_DIR}/tests/test_data/nested_print_tuple.json")

add_test(NAME test_args_print COMMAND interpreter_test "test_args_print" "${CMAKE_SOURCE_DIR}/tests/test_data/args_print.json")

add_test(NAME test_binary_op_add_number COMMAND interpreter_test "test_binary_op_add_number" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_add_number.json")
add_test(NAME test_binary_op_add_number_string COMMAND interpreter_test "test_binary_op_add_number_string" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_add_number_string.json")
add_test(NAME test_binary_op_add_string COMMAND interpreter_test "test_binary_op_add_string" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_add_string.json")
add_test(NAME test_binary_op_add_string_number COMMAND interpreter_test "test_binary_op_add_string_number" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_add_string_number.json")
add_test(NAME test_binary_op_and COMMAND interpreter_test "test_binary_op_and" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_and.json")
add_test(NAME test_binary_op_div_number COMMAND interpreter_test "test_binary_op_div_number" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_div_number.json")
add_test(NAME test_binary_op_eq_bool COMMAND interpreter_test "test_binary_op_eq_bool" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_eq_bool.json")
add_test(NAME test_binary_op_eq_number COMMAND interpreter_test "test_binary_op_eq_number" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_eq_number.json")
add_test(NAME test_binary_op_eq_string COMMAND interpreter_test "test_binary_op_eq_string" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_eq_string.json")
add_test(NAME test_binary_op_gt_number COMMAND interpreter_test "test_binary_op_gt_number" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_gt_number.json")
add_test(NAME test_binary_op_gte_number COMMAND interpreter_test "test_binary_op_gte_number" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_gte_number.json")
add_test(NAME test_binary_op_lt_number COMMAND interpreter_test "test_binary_op_lt_number" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_lt_number.json")
add_test(NAME test_binary_op_lte_number COMMAND interpreter_test "test_binary_op_lte_number" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_lte_number.json")
add_test(NAME test_binary_op_mul_number COMMAND interpreter_test "test_binary_op_mul_number" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_mul_number.json")
add_test(NAME test_binary_op_neq_bool COMMAND interpreter_test "test_binary_op_neq_bool" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_neq_bool.json")
add_test(NAME test_binary_op_neq_number COMMAND interpreter_test "test_binary_op_neq_number" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_neq_number.json")
add_test(NAME test_binary_op_neq_string COMMAND interpreter_test "test_binary_op_neq_string" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_neq_string.json")
add_test(NAME test_binary_op_or COMMAND interpreter_test "test_binary_op_or" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_or.json")
add_test(NAME test_binary_op_rem_number COMMAND interpreter_test "test_binary_op_rem_number" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_rem_number.json")
add_test(NAME test_binary_op_sub_number COMMAND interpreter_test "test_binary_op_sub_number" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_sub_number.json")

add_test(NAME test_combination COMMAND interpreter_test "test_combination" "${CMAKE_SOURCE_DIR}/tests/test_data/combination.json")
add_test(NAME test_fib COMMAND interpreter_test "test_fib" "${CMAKE_SOURCE_DIR}/tests/test_data/fib.json")
add_test(NAME test_print COMMAND interpreter_test "test_print" "${CMAKE_SOURCE_DIR}/tests/test_data/print.json")
add_test(NAME test_sum COMMAND interpreter_test "test_sum" "${CMAKE_SOURCE_DIR}/tests/test_data/sum.json")
add_test(NAME test_expresion COMMAND interpreter_test "test_expresion" "${CMAKE_SOURCE_DIR}/tests/test_data/expresion.json")

add_test(NAME test_closure_returned_with_param COMMAND interpreter_test "test_closure_returned_with_param" "${CMAKE_SOURCE_DIR}/tests/test_data/closure_returned_with_param.json")
add_test(NAME test_closure_returned_without_param COMMAND interpreter_test "test_closure_returned_without_param" "${CMAKE_SOURCE_DIR}/tests/test_data/closure_returned_without_param.json")
add_test(NAME test_closure_simple_with_param COMMAND interpreter_test "test_closure_simple_with_param" "${CMAKE_SOURCE_DIR}/tests/test_data/closure_simple_with_param.json")
add_test(NAME test_closure_simple_without_param COMMAND interpreter_test "test_closure_simple_without_param" "${CMAKE_SOURCE_DIR}/tests/test_data/closure_simple_without_param.json")
add_test(NAME test_closure_as_param COMMAND interpreter_test "test_closure_as_param" "${CMAKE_SOURCE_DIR}/tests/test_data/closure_as_param.json")
add_test(NAME test_closure_as_param_with_param COMMAND interpreter_test "test_closure_as_param_with_param" "${CMAKE_SOURCE_DIR}/tests/test_data/closure_as_param_with_param.json")

add_test(NAME test_fib_46 COMMAND interpreter_test "test_fib_46" "${CMAKE_SOURCE_DIR}/tests/test_data/fib_46.json")
add_test(NAME test_fib_5_print COMMAND interpreter_test "test_fib_5_print" "${CMAKE_SOURCE_DIR}/tests/test_data/fib_5_print.json")

##################################
# interpreter_exception_test.cpp #
##################################
add_executable(interpreter_exception_test src/interpreter_exception_test.cpp )
target_include_directories(interpreter_exception_test PUBLIC "${CMAKE_SOURCE_DIR}/rinha-compiler")
target_link_libraries(interpreter_exception_test PUBLIC rinha-compiler )

add_test(NAME test_binary_op_div_string_falha COMMAND interpreter_exception_test "test_binary_op_div_string_falha" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_div_string_falha.json")
add_test(NAME test_binary_op_eq_string_number_falha COMMAND interpreter_exception_test "test_binary_op_eq_string_number_falha" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_eq_string_number_falha.json")
add_test(NAME test_binary_op_neq_string_number_falha COMMAND interpreter_exception_test "test_binary_op_neq_string_number_falha" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_neq_string_number_falha.json")
add_test(NAME test_binary_op_sub_string_falha COMMAND interpreter_exception_test "test_binary_op_sub_string_falha" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_op_sub_string_falha.json")
add_test(NAME test_if_string_falha COMMAND interpreter_exception_test "test_if_string_falha" "${CMAKE_SOURCE_DIR}/tests/test_data/if_string_falha.json")
add_test(NAME test_binary_and_string_falha COMMAND interpreter_exception_test "test_binary_and_string_falha" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_and_string_falha.json")
add_test(NAME test_binary_gt_string_falha COMMAND interpreter_exception_test "test_binary_gt_string_falha" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_gt_string_falha.json")
add_test(NAME test_binary_gte_string_falha COMMAND interpreter_exception_test "test_binary_gte_string_falha" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_gte_string_falha.json")
add_test(NAME test_binary_lt_string_falha COMMAND interpreter_exception_test "test_binary_lt_string_falha" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_lt_string_falha.json")
add_test(NAME test_binary_lte_string_falha COMMAND interpreter_exception_test "test_binary_lte_string_falha" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_lte_string_falha.json")
add_test(NAME test_binary_or_string_falha COMMAND interpreter_exception_test "test_binary_or_string_falha" "${CMAKE_SOURCE_DIR}/tests/test_data/binary_or_string_falha.json")
add_test(NAME test_fun_arity_erro COMMAND interpreter_exception_test "test_fun_arity_erro" "${CMAKE_SOURCE_DIR}/tests/test_data/fun_arity_erro.json")
add_test(NAME test_call_function_wrong COMMAND interpreter_exception_test "test_call_function_wrong" "${CMAKE_SOURCE_DIR}/tests/test_data/call_function_wrong.json")