#include "../include/interpreter.hpp"
#include <tuple>
#include <variant>

namespace interpreter {
    using Type = std::variant<int, bool, std::string>;

    template<typename ... Ts>                                                 // (7) 
    struct Overload : Ts ... { 
        using Ts::operator() ...;
    };
    template<class... Ts> Overload(Ts...) -> Overload<Ts...>;

    Type run_int(Int&);
    Type run_str(Str&);
    Type run_call(Call&);
    Type run_binary(Binary&);
    Type run_function(Function&);
    Type run_let(Let&);
    Type run_if(If&);
    Type run_print(box<Print>&);
    Type run_first(First&);
    Type run_second(Second&);
    Type run_bool(Bool&);
    Type run_tuple(Tuple&);
    Type run_var(Var&);

    struct VisitTerm {
        Type operator()(Int& term){ return run_int(term);}
        Type operator()(Str& term){ return run_str(term);}
        Type operator()(Call& term){ return run_call(term);}
        Type operator()(Binary& term){ return run_binary(term);}
        Type operator()(Function& term){ return run_function(term);}
        Type operator()(Let& term){ return run_let(term);}
        Type operator()(If& term){ return run_if(term);}
        Type operator()(box<Print>& term){ return run_print(term);}
        Type operator()(First& term){ return run_first(term);}
        Type operator()(Second& term){ return run_second(term);}
        Type operator()(Bool& term){ return run_bool(term);}
        Type operator()(Tuple& term){ return run_tuple(term);}
        Type operator()(Var& term){ return run_var(term);}
        
        
    };

    Type run_int(Int& term){
        return term.value;
    }
    Type run_str(Str& term){
        return term.value;
    }
    Type run_call(Call& term){
        return 0;
    }
    Type run_binary(Binary& term){
        return 0;
    }
    Type run_function(Function& term){
        return 0;
    }
    Type run_let(Let& term){
        return 0;
    }
    Type run_if(If& term){
        return 0;
    }

    Type run_print(box<Print>& term){
        Type value = std::visit(VisitTerm{}, term->value);
        std::visit([](const auto &x) { std::cout << x << std::endl; }, value);
        return value;
    }

    Type run_first(First& term){

        Type value = std::visit(Overload{
                            [](Tuple& tuple) { return  tuple.first;},
                            [](auto&)   { 
                                std::cout << "First nao e uma tupla. TODO"; 
                                return 0;
                            }
                        }, term.value);

    }
    Type run_second(Second& term){return 0;}
    Type run_bool(Bool& term){return 0;}
    Type run_tuple(Tuple& term){return 0;}
    Type run_var(Var& term){return 0;}


    void walk(File file){
        std::visit(VisitTerm{}, file.expression);
    }
}