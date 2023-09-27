#include <interpreter_binary_operation.hpp>
#include <rinha_exception.hpp>
#include <walker.hpp>
#include <interpreter.hpp>

extern rinha_compiler::stack _stack;

namespace rinha_compiler::interpreter {


    template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
    template<class... Ts> overload(Ts...) -> overload<Ts...>;

    template <class Visitor, class... Variants>
    constexpr Type visit(Visitor&& vis, Variants&&... vars);

    void bin_op(box<Binary>& term){
        std::visit(rinha_compiler::walker::VisitTerm{}, term->lhs.terms.front());
        std::visit(rinha_compiler::walker::VisitTerm{}, term->rhs.terms.front());
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
}