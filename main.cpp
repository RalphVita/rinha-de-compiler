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
    try{
        std::string path = argv[1];
        auto json_data = *daw::read_file(path);

        File file = json_to_ast::parser(json_data);


        interpreter::walk(file);
    }
    catch(rinha_compiler::RinhaException &ex){
        std::cout << ex.message() << std::endl;
        throw ex;
    }
}