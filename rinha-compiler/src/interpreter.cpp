#include "../include/interpreter.hpp"

// namespace interpreter {
//     Type run_print(box<Print>& term);
// }

namespace interpreter {
    using Type = std::variant<int, bool, std::string>;

    Type run_print(box<Print>&);

    struct VisitTerm {
        Type operator()(box<Print>& term){ return interpreter::run_print(term);}
        Type operator()(Str& term)       { return term.value;}
    };

    Type run_print(box<Print>& term){
        Type value = std::visit(VisitTerm{}, term->value);
        std::visit([](const auto &x) { std::cout << x << std::endl; }, value);
        return value;
    }


    void walk(File file){
        std::visit(VisitTerm{}, file.expression);
    }
}