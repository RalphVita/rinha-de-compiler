#include <interpreter.hpp>
#include <tuple>
#include <variant>
#include <string>
#include <walker.hpp>
#include <stack.hpp>

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>; // line not needed in C++20...

stack _stack;

void bin_op(box<Binary>& term){
    std::visit(walker::VisitTerm{}, term->lhs.terms.front());
    std::visit(walker::VisitTerm{}, term->rhs.terms.front());
}

void run_plus(box<Binary>& term) {
    bin_op(term);

    Type r = _stack.pop();
    Type l = _stack.pop();

    struct sum_visit
    {
        Type operator()(std::string l, std::string r){ return l + r;}
        Type operator()(std::string l, int r){ return l + std::to_string(r);}
        Type operator()(int l, std::string r){ return std::to_string(l) + r;}
        Type operator()(int l, int r){ return l + r;}
        //Type operator()(auto &l, auto &r){ throw 555;}TODO
    };
    

    Type result = std::visit(sum_visit{}, l, r);

    _stack.push(result);
}


void run_minus(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) - std::get<int>(r));
    else
        throw 555;
}

void run_times(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) * std::get<int>(r));
    else
        throw 555;
}

void run_over(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) / std::get<int>(r));
    else
        throw 555;
}

void run_rem(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) % std::get<int>(r));
    else
        throw 555;
}

void run_eq(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    _stack.push(std::get<int>(l) == std::get<int>(r));
}

void run_neq(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    _stack.push(std::get<int>(l) != std::get<int>(r));
}

void run_lt(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) < std::get<int>(r));
    else
        throw 555;
}

void run_rt(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) > std::get<int>(r));
    else
        throw 555;
}

void run_lte(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) <= std::get<int>(r));
    else
        throw 555;
}

void run_gte(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) >= std::get<int>(r));
    else
        throw 555;
}

void run_and(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<bool>(l) && std::holds_alternative<bool>(r))
        _stack.push(std::get<int>(l) && std::get<int>(r));
    else
        throw 555;
}

void run_or(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<bool>(l) && std::holds_alternative<bool>(r))
        _stack.push(std::get<int>(l) || std::get<int>(r));
    else
        throw 555;
}




void run_int(Int& term){
    _stack.push(term.value);
}
void run_str(Str& term){
    _stack.push(term.value);
}
void run_call(box<Call>& term){
    
}
void run_binary(box<Binary>& term){
    
    // switch (term->op)
    // {
    // case /* constant-expression */:
    //     /* code */
    //     break;
    
    // default:
    //     break;
    // }
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
    //std::cout << _stack.pop() << std::endl;
    std::visit([](const auto &x) { std::cout << x << std::endl; }, _stack.pop());
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
void run_second(box<Second>& term){
}
void run_bool(Bool& term){
    _stack.push(term.value);
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