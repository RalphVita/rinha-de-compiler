#include <interpreter.hpp>
#include <tuple>
#include <variant>
#include <string>
#include <walker.hpp>
std::string x;
void run_int(Int& term){
    //return term.value;
}
void run_str(Str& term){
    //return term.value;
    x = term.value;
}
void run_call(box<Call>& term){
    //return 0;
}
void run_binary(box<Binary>& term){
    //return 0;
}
void run_function(box<Function>& term){
    //return 0;
}
void run_let(box<Let>& term){
    //return 0;
}
void run_if(box<If>& term){
    //return 0;
}

void run_print(box<Print>& term){
    std::visit(walker::VisitTerm{}, term->value.terms.front());
    std::cout << x << std::endl;
    //std::visit([](const auto &x) { std::cout << x << std::endl; }, value);
    //return value;
    ////return 0;
}

void run_first(box<First>& term){
    //return 0;
    // void value = std::visit(Overload{
    //                     [](box<Tuple>& tuple) { return  tuple.first;},
    //                     [](box<auto>&)   { 
    //                         std::cout << "First nao e uma tupla. TODO"; 
    //                         return 0;
    //                     }
    //                 }, term.value);

}
void run_second(box<Second>& term){//return 0;
}
void run_bool(Bool& term){//return 0;
}
void run_tuple(box<Tuple>& term){//return 0;
}
void run_var(box<Var>& term){//return 0;
}
namespace interpreter {    
    // template<typename ... Ts>                                                 // (7) 
    // struct Overload : Ts ... { 
    //     using Ts::operator() ...;
    // };
    // template<class... Ts> Overload(Ts...) -> Overload<Ts...>;

    //namespace walker{
        
    //}


    void walk(File file){
        std::visit(walker::VisitTerm{}, file.expression.terms.front());
    }
}