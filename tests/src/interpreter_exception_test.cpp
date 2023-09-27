#include <sstream>
#include <iostream>
#include <string>
#include <daw/daw_read_file.h>
#include <rinha-compiler.hpp>

int main(int argc, char **argv ){

    std::string test_name = argv[1];
    std::string path = argv[2];

    auto json_data = *daw::read_file( path );
    File file = json_to_ast::parser(json_data);

    try{
        rinha_compiler::interpreter::walk(file);
    }
    catch(rinha_compiler::RinhaException &ex){
        std::cout << ex.message() << std::endl;
        return 0;
    }

    return 1;
}