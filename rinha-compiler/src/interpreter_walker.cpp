#include <interpreter.hpp>
#include <walker.hpp>
#include <rinha_exception.hpp>
#include <type.hpp>
#include <interpreter_binary_operation.hpp>
#include <interpreter_function.hpp>
#include <stack>

rinha_compiler::stack _stack;
rinha_compiler::Memory _memory;
rinha_compiler::SymbolTable* variable_symbol_table;
int current_scope;

extern rinha_compiler::FunctionCache function_cache;
namespace rinha_compiler::walker {

using namespace rinha_compiler::interpreter;

    void run_int(Int& term){
        _stack.push(term.value);
    }
    void run_str(Str& term){
        _stack.push(term.value);
    }

     void run_var_decl(box<Let>& term){
        Term value = term->value.terms.front();
        std::string id = term->name.text;
        rinha_compiler::Symbol symbol = rinha_compiler::init_symbol(id, current_scope);

        symbol = variable_symbol_table->Put(id, symbol);

        std::visit(walker::VisitTerm{}, value);
        Type result = _stack.pop();

        _memory.store(symbol, result);
     }

    void run_let(box<Let>& term){
        Term value = term->value.terms.front();
        if(std::holds_alternative<box<Function>>(value))
            run_function_decl(term);
        else
            run_var_decl(term);

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
        function_cache.set_change_scope("Print");
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
            void operator()(Term &x){
                throw rinha_compiler::RinhaException("Váriavel inválida para Print.");
            }
        };
        

        std::visit(sum_visit{}, value);
        std::cout << std::endl;

        _stack.push(value);
    }

    void run_first(box<First>& term){
        std::visit(walker::VisitTerm{}, term->value.terms.front());

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
        rinha_compiler::Symbol symbol = variable_symbol_table->Get(id);
        //if(symbol.is_function)
        //    throw rinha_compiler::RinhaException("Simbolo " + id + ", não encontrado na tabela de simbolos.", term->location);

        trace(id);
        Type value = _memory.load(symbol);

        _stack.push(value);
    }
}
