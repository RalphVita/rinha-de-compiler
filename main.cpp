#include <rinha-compiler.hpp>

#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <map>
#include <variant>







int main() {
    std::string_view test_001_t_json_data = R"({
    "name": "print.rinha",
    "expression": {
        "kind": "Print",
        "value": {
        "value": "Hello world",
        "kind": "Str",
        
        "location": {
            "start": 7,
            "end": 20,
            "filename": "print.rinha"
        }
        },
        "location": {
        "start": 0,
        "end": 21,
        "filename": "print.rinha"
        }
    },
    "location": {
        "start": 0,
        "end": 21,
        "filename": "print.rinha"
    }
    })";
    
    
    File file = json_to_ast::parser(test_001_t_json_data);

    interpreter::walk(file);
    
}