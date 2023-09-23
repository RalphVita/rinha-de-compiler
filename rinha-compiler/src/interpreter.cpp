#include <interpreter.hpp>
#include <tuple>
#include <variant>
#include <string>
#include <walker.hpp>
#include <stack.hpp>
#include <box.hpp>
#include <ast.hpp>
#include <memory.hpp>
#include <symbol_table.hpp>

using Type = std::variant<int, bool, std::string>;


stack _stack;
rinha_compiler::Memory _memory = rinha_compiler::Memory();
std::unique_ptr<rinha_compiler::SymbolTable> symbolTable;// = std::move(rinha_compiler::SymbolTable());
int current_scope;


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

void run_gt(box<Binary>& term) {
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

// box<Let> find_func_decl(std::string function_name){
//     Let y;
//     box<Let> x = symbolTable->Get(function_name).;
//     return x;
// }

void load_paran_list(box<Function>& function){
    for (auto parameter = function->parameters.rend(); parameter != function->parameters.rbegin(); --parameter){
        Type value = _stack.pop();
        std::string id = parameter->text;
        rinha_compiler::Symbol symbol = rinha_compiler::init_symbol(id, current_scope);

        symbolTable->Put(id, symbol);

        _memory.store(symbol, value);
    }
}

void run_call(box<Call>& term){
    int arity = term->arguments.terms.size();
    int saved_scope = current_scope;
    if(arity > 0){
        //Carrega argumentos na pilha
        for(auto arg: term->arguments.terms)
            std::visit(walker::VisitTerm{}, arg);
    }

    //Recupera nome da função
    std::visit(walker::VisitTerm{}, term->callee.terms.front());
    Type function_name = _stack.pop();
    if(!std::holds_alternative<std::string>(function_name))
        throw 555;
    
    std::string id = std::get<std::string>(function_name);
    rinha_compiler::Symbol symbol = symbolTable->Get(id);
    current_scope = symbol.scope;
    _memory.increment(current_scope + 1);
    _memory.push(symbol.scope);
    
    //Busca e Aponta para o bloco da função na AST
    auto let_function = std::get<box<Let>>(symbol.term);//find_func_decl(id);

    //Varre a o bloco da função recursivamente
    std::visit(walker::VisitTerm{}, let_function->value.terms.front());

    _memory.pop(symbol.scope);
    current_scope = saved_scope;
}
void run_binary(box<Binary>& term){
    
    switch (term->op)
    {
        case BinaryOp::Add:
            run_plus(term);
            break;
        case BinaryOp::Sub:
            run_minus(term);
            break;
        case BinaryOp::Mul:
            run_times(term);
            break;
        case BinaryOp::Div:
            run_over(term);
            break;
        case BinaryOp::Rem:
            run_rem(term);
            break;
        case BinaryOp::Eq:
            run_eq(term);
            break;
        case BinaryOp::Neq:
            run_neq(term);
            break;
        case BinaryOp::Lt:
            run_lt(term);
            break;
        case BinaryOp::Gt:
            run_gt(term);
            break;
        case BinaryOp::Lte:
            run_lte(term);
            break;
        case BinaryOp::Gte:
            run_gte(term);
            break;
        case BinaryOp::And:
            run_and(term);
            break;
        case BinaryOp::Or:
            run_or(term);
            break;
        default:
            throw 555;
            break;
    }
}
void run_function(box<Function>& term){
    auto symbol_table_function = std::unique_ptr<rinha_compiler::SymbolTable>(new rinha_compiler::SymbolTable(symbolTable));
    load_paran_list(term);

    std::visit(walker::VisitTerm{}, term->value.terms.front());

    symbolTable = symbol_table_function->GetParent();
}

void run_function_decl(box<Let>& term){
    std::string id = term->name.text;
    Term value = term->value.terms.front();
    current_scope++;
    _memory.increment(current_scope + 1);

    rinha_compiler::Symbol symbol = rinha_compiler::init_symbol(id, current_scope, term);

    symbolTable->Put(id, symbol);

    current_scope--;
}

void run_let(box<Let>& term){
    Term value = term->value.terms.front();
    if(std::holds_alternative<box<Function>>(value)){
        run_function_decl(term);
    }
    else {
        std::string id = term->name.text;
        rinha_compiler::Symbol symbol = rinha_compiler::init_symbol(id, current_scope);

        symbolTable->Put(id, symbol);

        std::visit(walker::VisitTerm{}, value);
        Type result = _stack.pop();

        _memory.store(symbol, result);
    }

    std::visit(walker::VisitTerm{}, term->next.terms.front());
}
void run_if(box<If>& term){
    std::visit(walker::VisitTerm{}, term->condition.terms.front());
    Type test = _stack.pop();
    if(!std::holds_alternative<bool>(test))
        throw 555;
    if(std::get<bool>(test)){
        std::visit(walker::VisitTerm{}, term->then.terms.front());
    }else{
        std::visit(walker::VisitTerm{}, term->otherwise.terms.front());
    }
}

void run_print(box<Print>& term){
    std::visit(walker::VisitTerm{}, term->value.terms.front());
    Type value = _stack.pop();
    std::visit([](const auto &x) { std::cout << x << std::endl; }, value);
    _stack.push(value);
}

void run_first(box<First>& term){
    std::visit(walker::VisitTerm{}, term->value.terms.front());
    Type second = _stack.pop();
    Type first = _stack.pop();

    _stack.push(first);
}
void run_second(box<Second>& term){
    std::visit(walker::VisitTerm{}, term->value.terms.front());
    Type second = _stack.pop();
    Type first = _stack.pop();

    _stack.push(second);
}
void run_bool(Bool& term){
    _stack.push(term.value);
}
void run_tuple(box<Tuple>& term){
    std::visit(walker::VisitTerm{}, term->first.terms.front());
    std::visit(walker::VisitTerm{}, term->second.terms.front());
}

//Usando uma váriavel
void run_var(box<Var>& term){
    std::string id = term->text;
    rinha_compiler::Symbol symbol = symbolTable->Get(id);
    Type value = _memory.load(symbol);

    _stack.push(value);
}
namespace interpreter {
    void walk(File file){
        current_scope = 0;
        _memory.increment(current_scope + 1);
        symbolTable = std::unique_ptr<rinha_compiler::SymbolTable>(new rinha_compiler::SymbolTable());
        std::visit(walker::VisitTerm{}, file.expression.terms.front());
    }
}
