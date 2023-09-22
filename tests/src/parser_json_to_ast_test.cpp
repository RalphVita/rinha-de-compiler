#include <iostream>
#include <string>
#include <daw/daw_read_file.h>
#include <rinha-compiler.hpp>

int test_parser_json_print(std::string);

int main(int argc, char **argv ){

    std::string test_name = argv[1];
    std::cout << test_name << std::endl;

    if(test_name == "test_parser_json_print"){
        std::string path = argv[2];
        return test_parser_json_print(path);
    }
    
    return 1;
}

int test_parser_json_print(std::string path) {
    auto json_data = *daw::read_file( path );
    File file = json_to_ast::parser(json_data);
    
    int check_kind = 0;//std::holds_alternative<box<struct Print>>(file.expression) ? 0 : 1;

    return check_kind;
}