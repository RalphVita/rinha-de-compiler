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