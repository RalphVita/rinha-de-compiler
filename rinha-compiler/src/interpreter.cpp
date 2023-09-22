#include <interpreter.hpp>
#include <tuple>
#include <variant>


namespace interpreter {
    using Type = std::variant<int, bool, std::string>;

    // template<typename ... Ts>                                                 // (7) 
    // struct Overload : Ts ... { 
    //     using Ts::operator() ...;
    // };
    // template<class... Ts> Overload(Ts...) -> Overload<Ts...>;

    Type run_int(Int&);
    Type run_str(Str&);
    Type run_call(box<Call>&);
    Type run_binary(box<Binary>&);
    Type run_function(box<Function>&);
    Type run_let(box<Let>&);
    Type run_if(box<If>&);
    Type run_print(box<Print>&);
    Type run_first(box<First>&);
    Type run_second(box<Second>&);
    Type run_bool(Bool&);
    Type run_tuple(box<Tuple>&);
    Type run_var(box<Var>&);

    struct VisitTerm {
        Type operator()(Int& term){ return run_int(term);}
        Type operator()(Str& term){ return run_str(term);}
        Type operator()(box<Call>& term){ return run_call(term);}
        Type operator()(box<Binary>& term){ return run_binary(term);}
        Type operator()(box<Function>& term){ return run_function(term);}
        Type operator()(box<Let>& term){ return run_let(term);}
        Type operator()(box<If>& term){ return run_if(term);}
        Type operator()(box<Print>& term){ return run_print(term);}
        Type operator()(box<First>& term){ return run_first(term);}
        Type operator()(box<Second>& term){ return run_second(term);}
        Type operator()(Bool& term){ return run_bool(term);}
        Type operator()(box<Tuple>& term){ return run_tuple(term);}
        Type operator()(box<Var>& term){ return run_var(term);}
        
        
    };

    Type run_int(Int& term){
        return term.value;
    }
    Type run_str(Str& term){
        return term.value;
    }
    Type run_call(box<Call>& term){
        return 0;
    }
    Type run_binary(box<Binary>& term){
        return 0;
    }
    Type run_function(box<Function>& term){
        return 0;
    }
    Type run_let(box<Let>& term){
        return 0;
    }
    Type run_if(box<If>& term){
        return 0;
    }

    Type run_print(box<Print>& term){
        Type value = std::visit(VisitTerm{}, term->value.terms.front());
        std::visit([](const auto &x) { std::cout << x << std::endl; }, value);
        return value;
        //return 0;
    }

    Type run_first(box<First>& term){
        return 0;
        // Type value = std::visit(Overload{
        //                     [](box<Tuple>& tuple) { return  tuple.first;},
        //                     [](box<auto>&)   { 
        //                         std::cout << "First nao e uma tupla. TODO"; 
        //                         return 0;
        //                     }
        //                 }, term.value);

    }
    Type run_second(box<Second>& term){return 0;}
    Type run_bool(Bool& term){return 0;}
    Type run_tuple(box<Tuple>& term){return 0;}
    Type run_var(box<Var>& term){return 0;}


    void walk(File file){
        std::visit(VisitTerm{}, file.expression.terms.front());
    }
}