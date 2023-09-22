#include <iostream>
#include <string>
#include <daw/daw_read_file.h>
#include <rinha-compiler.hpp>

int test_parser_json_print(std::string);
int test_parser_json_sum(std::string);
int test_parser_json_fib(std::string);

int main(int argc, char **argv ){

    std::string test_name = argv[1];
    std::cout << test_name << std::endl;
    std::string path = argv[2];

    if(test_name == "test_parser_json_print")
        return test_parser_json_print(path);
    else if(test_name == "test_parser_json_sum")
        return test_parser_json_sum(path);
    else if(test_name == "test_parser_json_fib")
        return test_parser_json_fib(path);
    
    return 1;
}

int test_parser_json_print(std::string path) {
    auto json_data = *daw::read_file( path );
    File file = json_to_ast::parser(json_data);
    
    int check_kind = std::holds_alternative<box<struct Print>>(file.expression.terms.front()) ? 0 : 1;

    return check_kind;
}

int test_parser_json_sum(std::string path) {
    auto json_data = *daw::read_file( path );
    File file = json_to_ast::parser(json_data);
    
    int check_kind = std::holds_alternative<box<struct Let>>(file.expression.terms.front()) ? 0 : 1;

    return check_kind;
}

int test_parser_json_fib(std::string path) {
    auto json_data = *daw::read_file( path );
    File file = json_to_ast::parser(json_data);
    
    int check_kind = std::holds_alternative<box<struct Let>>(file.expression.terms.front()) ? 0 : 1;

    return check_kind;
}