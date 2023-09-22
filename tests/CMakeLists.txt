cmake_minimum_required(VERSION 3.22.1)


add_executable(parser_json_to_ast_test src/parser_json_to_ast_test.cpp )
target_include_directories(parser_json_to_ast_test PUBLIC "${CMAKE_SOURCE_DIR}/rinha-compiler")
target_link_libraries(parser_json_to_ast_test PUBLIC rinha-compiler )


add_test(NAME test_parser_json_print COMMAND parser_json_to_ast_test "test_parser_json_print" "${CMAKE_SOURCE_DIR}/tests/test_data/print.json")
add_test(NAME test_parser_json_sum COMMAND parser_json_to_ast_test "test_parser_json_sum" "${CMAKE_SOURCE_DIR}/tests/test_data/sum.json")
add_test(NAME test_parser_json_fib COMMAND parser_json_to_ast_test "test_parser_json_fib" "${CMAKE_SOURCE_DIR}/tests/test_data/fib.json")