#include <rinha-compiler.hpp>

#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <map>
#include <variant>
#include <daw/daw_read_file.h>







int main(int argc, char **argv) {

    //std::string path = "/mnt/c/WORKSPACE/source/RalphVita/rinha-de-compiler/tests/test_data/combination.json";
    std::string path = argv[2];
    std::string compiler_type = argv[1];
    auto json_data = *daw::read_file( path );
    
    //std::cout << json_data << std::endl;
    
    File file = json_to_ast::parser(json_data);

    if(compiler_type == "1")
        interpreter::walk(file);
    else
        rinha_compiler::compiler::walk(file);
    
}