#include <symbol.hpp>
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
#include <rinha_exception.hpp>



stack _stack;
rinha_compiler::Memory _memory = rinha_compiler::Memory();
rinha_compiler::SymbolTable* symbolTable;// = std::move(rinha_compiler::SymbolTable());
int current_scope;

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

template <class Visitor, class... Variants>
constexpr Type visit(Visitor&& vis, Variants&&... vars);


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
        sum_visit(box<Binary>& _term) : term(_term){}
        Type operator()(std::string l, std::string r){ return l + r;}
        Type operator()(std::string l, int r){ return l + std::to_string(r);}
        Type operator()(int l, std::string r){ return std::to_string(l) + r;}
        Type operator()(int l, int r){ return l + r;}
        Type operator()(box<tupla> &l, box<tupla> &r){
            throw rinha_compiler::RinhaException("Tipos inválidos para operação binária SUM", term->location);
            return false;
        }
        Type operator()(std::string l, box<tupla> &r){
            throw rinha_compiler::RinhaException("Tipos inválidos para operação binária SUM", term->location);
            return false;
        }
        Type operator()(int l, box<tupla> &r){
            throw rinha_compiler::RinhaException("Tipos inválidos para operação binária SUM", term->location);
            return false;
        }
        Type operator()(box<tupla> &l, std::string r){
            throw rinha_compiler::RinhaException("Tipos inválidos para operação binária SUM", term->location);
            return false;
        }
        Type operator()(box<tupla> &l, int r){
            throw rinha_compiler::RinhaException("Tipos inválidos para operação binária SUM", term->location);
            return false;
        }
        box<Binary> &term;
    };

    Type result = std::visit(sum_visit{term}, l, r);

    _stack.push(result);
}


void run_minus(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) - std::get<int>(r));
    else
        throw rinha_compiler::RinhaException("SUB só aceita Number.", term->location);
}

void run_times(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) * std::get<int>(r));
    else
        throw rinha_compiler::RinhaException("Mul só aceita Number.", term->location);
}

void run_over(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) / std::get<int>(r));
    else
        throw rinha_compiler::RinhaException("DIV só aceita Number.", term->location);
}

void run_rem(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) % std::get<int>(r));
    else
        throw rinha_compiler::RinhaException("REM só aceita Number.", term->location);
}

void run_eq(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    auto eq_visit = overload {
        [](std::string l, std::string r){ return l == r;},
        [](bool l, bool r){ return l == r;},
        [](int l, int r){ return l == r;},
        [&term](auto, auto) { 
            throw rinha_compiler::RinhaException("Tipos inválidos para operação binária EQ", term->location);
            return false;
        }
    };

    Type result = std::visit(eq_visit, l, r);

    _stack.push(result);
}

void run_neq(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    auto eq_visit = overload {
        [](std::string l, std::string r){ return l != r;},
        [](bool l, bool r){ return l != r;},
        [](int l, int r){ return l != r;},
        [&term](auto, auto) { 
            throw rinha_compiler::RinhaException("Tipos inválidos para operação binária NEQ", term->location);
            return false;
        }
    };

    Type result = std::visit(eq_visit, l, r);

    _stack.push(result);
}

void run_lt(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) < std::get<int>(r));
    else
        throw rinha_compiler::RinhaException("Tipos inválidos para operação binária LT", term->location);
}

void run_gt(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) > std::get<int>(r));
    else
        throw rinha_compiler::RinhaException("Tipos inválidos para operação binária GT", term->location);
}

void run_lte(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) <= std::get<int>(r));
    else
        throw rinha_compiler::RinhaException("Tipos inválidos para operação binária LTE", term->location);
}

void run_gte(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<int>(l) && std::holds_alternative<int>(r))
        _stack.push(std::get<int>(l) >= std::get<int>(r));
    else
        throw rinha_compiler::RinhaException("Tipos inválidos para operação binária GTE", term->location);
}

void run_and(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<bool>(l) && std::holds_alternative<bool>(r))
        _stack.push(std::get<bool>(l) && std::get<bool>(r));
    else
        throw rinha_compiler::RinhaException("Tipos inválidos para operação binária AND", term->location);
}

void run_or(box<Binary>& term) {
    bin_op(term);
    Type r = _stack.pop();
    Type l = _stack.pop();

    if(std::holds_alternative<bool>(l) && std::holds_alternative<bool>(r))
        _stack.push(std::get<bool>(l) || std::get<bool>(r));
    else
        throw rinha_compiler::RinhaException("Tipos inválidos para operação binária OR", term->location);
}




void run_int(Int& term){
    _stack.push(term.value);
}
void run_str(Str& term){
    _stack.push(term.value);
}

void load_paran_list(box<Function>& function){
    auto parameters = function->parameters;
    for (int i = parameters.size() - 1; i >= 0; i--)
    {
        Type value = _stack.pop();
        std::string id = parameters[i].text;
        rinha_compiler::Symbol symbol = rinha_compiler::init_symbol(id, current_scope);

        symbol = symbolTable->Put(id, symbol);

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
        throw rinha_compiler::RinhaException("Nome de função inválido.", term->location);
    
    std::string id = std::get<std::string>(function_name);
    rinha_compiler::Symbol symbol = symbolTable->Get(id);
    current_scope = symbol.scope + 1;
    _memory.increment(current_scope + 1);
    _memory.push(current_scope);
    
    //Busca e Aponta para o bloco da função na AST
    auto let_function = std::get<box<Let>>(symbol.term);//find_func_decl(id);

    //Varre a o bloco da função recursivamente
    std::visit(walker::VisitTerm{}, let_function->value.terms.front());

    _memory.pop(current_scope);
    current_scope = saved_scope;
}
void run_binary(box<Binary>& term){
    
    switch (term->op)
    {
        case BinaryOp::Add:
            trace("run_plus");
            run_plus(term);
            break;
        case BinaryOp::Sub:
            trace("run_minus");
            run_minus(term);
            break;
        case BinaryOp::Mul:
            trace("run_times");
            run_times(term);
            break;
        case BinaryOp::Div:
            trace("run_over");
            run_over(term);
            break;
        case BinaryOp::Rem:
            trace("run_rem");
            run_rem(term);
            break;
        case BinaryOp::Eq:
            trace("run_eq");
            run_eq(term);
            break;
        case BinaryOp::Neq:
            trace("run_neq");
            run_neq(term);
            break;
        case BinaryOp::Lt:
            trace("run_lt");
            run_lt(term);
            break;
        case BinaryOp::Gt:
            trace("run_gt");
            run_gt(term);
            break;
        case BinaryOp::Lte:
            trace("run_lte");
            run_lte(term);
            break;
        case BinaryOp::Gte:
            trace("run_gte");
            run_gte(term);
            break;
        case BinaryOp::And:
            trace("run_and");
            run_and(term);
            break;
        case BinaryOp::Or:
            trace("run_or");
            run_or(term);
            break;
        default:
            throw rinha_compiler::RinhaException("Operação binária inválida", term->location);
            break;
    }
}
void run_function(box<Function>& term){
    rinha_compiler::SymbolTable* symbol_table_function = new rinha_compiler::SymbolTable(symbolTable);
    symbolTable = symbol_table_function;
    load_paran_list(term);

    std::visit(walker::VisitTerm{}, term->value.terms.front());

    symbolTable = symbol_table_function->GetParent();
}

void run_function_decl(box<Let>& term){
    std::string id = term->name.text;
    Term value = term->value.terms.front();
    //current_scope++;
    _memory.increment(current_scope + 1);

    rinha_compiler::Symbol symbol = rinha_compiler::init_symbol(id, current_scope, term);

    symbol = symbolTable->Put(id, symbol);
    _memory.store(symbol, id);

    //current_scope--;
}

void run_let(box<Let>& term){
    Term value = term->value.terms.front();
    if(std::holds_alternative<box<Function>>(value)){
        run_function_decl(term);
    }
    else {
        std::string id = term->name.text;
        rinha_compiler::Symbol symbol = rinha_compiler::init_symbol(id, current_scope);

        symbol = symbolTable->Put(id, symbol);
        //symbol = symbolTable->Get(id);

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
        throw rinha_compiler::RinhaException("IF só aceita bool", term->location);
    if(std::get<bool>(test)){
        std::visit(walker::VisitTerm{}, term->then.terms.front());
    }else{
        std::visit(walker::VisitTerm{}, term->otherwise.terms.front());
    }
}

void run_print(box<Print>& term){
    std::visit(walker::VisitTerm{}, term->value.terms.front());
    Type value = _stack.pop();

    struct sum_visit
    {
        void operator()(std::string x){ std::cout << x;}
        void operator()(bool x){ std::cout << (x ? "true": "false") ;}
        void operator()(int x){ std::cout << x;}
        void operator()(box<tupla> &x){ 
            std::cout << "("; 
            std::visit(*this, std::get<0>(x->value));
            std::cout << ", "; 
            std::visit(*this, std::get<1>(x->value));
            std::cout << ")";
        }
    };
    

    std::visit(sum_visit{}, value);
    std::cout << std::endl;

    //std::visit([](const auto &x) { std::cout << x << std::endl; }, value);
    _stack.push(value);
}

void run_first(box<First>& term){
    std::visit(walker::VisitTerm{}, term->value.terms.front());
    //Type second = _stack.pop();
    //Type first = _stack.pop();
    auto _tupla = _stack.pop();
    if(std::holds_alternative<box<struct tupla>>(_tupla)){
        Type first = std::get<0>(std::get<box<struct tupla>>(_tupla)->value);
        _stack.push(first);
    }
    else
        throw rinha_compiler::RinhaException("FIRST só aceita Tupla.", term->location);
}
void run_second(box<Second>& term){
    std::visit(walker::VisitTerm{}, term->value.terms.front());
    //Type second = _stack.pop();
    //Type first = _stack.pop();
    auto _tupla = _stack.pop();
    if(std::holds_alternative<box<struct tupla>>(_tupla)){
        Type second = std::get<1>(std::get<box<struct tupla>>(_tupla)->value);
        _stack.push(second);
    }
    else
        throw rinha_compiler::RinhaException("SECOND só aceita Tupla.", term->location);
}
void run_bool(Bool& term){
    _stack.push(term.value);
}
void run_tuple(box<Tuple>& term){
    std::visit(walker::VisitTerm{}, term->first.terms.front());
    std::visit(walker::VisitTerm{}, term->second.terms.front());
    Type second = _stack.pop();
    Type first = _stack.pop();
    auto result = std::make_tuple(first, second);
    tupla t(result);
    _stack.push(t);
}

//Usando uma váriavel
void run_var(box<Var>& term){
    std::string id = term->text;
    trace(id);
    rinha_compiler::Symbol symbol = symbolTable->Get(id);
    trace(id);
    Type value = _memory.load(symbol);

    _stack.push(value);
}
namespace interpreter {
    void walk(File file){
        current_scope = 0;
        _memory.increment(current_scope + 1);
        _memory.push(current_scope);
        symbolTable = new rinha_compiler::SymbolTable();
        std::visit(walker::VisitTerm{}, file.expression.terms.front());
    }
}
