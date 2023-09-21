#include <rinha-compiler.hpp>

#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <map>
#include <variant>





using Type = std::variant<int, bool, std::string>;

struct VisitTerm {
    Type operator()(box<Print>& term){ 
      Type value = std::visit(*this, term->value);
      std::visit([](const auto &x) { std::cout << x << std::endl; }, value);
      return value;
    }
    Type operator()(Str& term)       { return term.value;}
};

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

    std::visit(VisitTerm{}, file.expression);
}