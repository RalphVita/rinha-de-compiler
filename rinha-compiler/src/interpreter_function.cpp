#include <interpreter_function.hpp>
#include <interpreter.hpp>
#include <walker.hpp>
#include <rinha_exception.hpp>
#include <type.hpp>
#include <stack>
#include <function_cache.hpp>
#include <box.hpp>
#include <ast.hpp>

extern rinha_compiler::stack _stack;
extern rinha_compiler::Memory _memory;
extern rinha_compiler::SymbolTable* variable_symbol_table;
extern int current_scope;
rinha_compiler::FunctionCache function_cache;

namespace rinha_compiler::walker {
    void load_arguments_onto_stack(box<Call>&);
    void create_page_memory(int);
    void delete_page_memory(int);
    Type get_function_callee(box<Call>&);
    Term get_function_pointer(box<tupla>&);
    std::string get_function_name(box<tupla>&);

    void run_function(box<Function>&);

    void run_call(box<Call>& term){
        int saved_scope = current_scope;

        load_arguments_onto_stack(term);

        Type function_callee = get_function_callee(term);

        if(!std::holds_alternative<box<tupla>>(function_callee))
        {
            _stack.push(function_callee);
            return;
        }
        //     throw rinha_compiler::RinhaException("Nome de função inválido.", term->location);
        
        // return std::get<box<tupla>>(function_name_point);
        auto function_name_pointer = std::get<box<tupla>>(function_callee);

        std::string function_name = get_function_name(function_name_pointer);
        Term function_pointer = get_function_pointer(function_name_pointer);

        rinha_compiler::Symbol symbol = variable_symbol_table->Get(function_name);
        
        //Indica ao cache que vai entrar em nova função
        function_cache.input_function(function_name);
        
        //Muda de escopo
        //A função sempre é salva com o espopo da parent. Então o novo escopo é:
        current_scope = symbol.scope + 1;

        create_page_memory(current_scope);
        
        //Aponta para o bloco da função na AST
        auto let_function = std::get<box<Let>>(function_pointer);

        //Varre o bloco da função recursivamente
        std::visit(walker::VisitTerm{}, let_function->value.terms.front());

        delete_page_memory(current_scope);

        current_scope = saved_scope;
    }

    void run_closure(box<Function>& term){
        int saved_scope = current_scope;
        rinha_compiler::SymbolTable* symbol_table_function = new rinha_compiler::SymbolTable(variable_symbol_table);
        variable_symbol_table = symbol_table_function;
        
        //Muda de escopo
        //A função sempre é salva com o espopo da parent. Então o novo escopo é:
        current_scope++;

        create_page_memory(current_scope);


        load_param_list_in_memory(term);
        // auto parameters = term->parameters;
        // for (int i = parameters.size() - 1; i >= 0; i--)
        // {
        //     Type value = _stack.pop();
        //     std::string id = parameters[i].text;
        //     rinha_compiler::Symbol symbol = rinha_compiler::init_symbol(id, current_scope);

        //     symbol = variable_symbol_table->Put(id, symbol);

        //     _memory.store(symbol, value);
        // }

        std::visit(walker::VisitTerm{}, term->value.terms.front());


        delete_page_memory(current_scope);

        current_scope = saved_scope;


        variable_symbol_table = symbol_table_function->GetParent();
    }

    void run_function(box<Function>& term){
        rinha_compiler::SymbolTable* symbol_table_function = new rinha_compiler::SymbolTable(variable_symbol_table);
        variable_symbol_table = symbol_table_function;


        load_param_list_in_memory(term);

        std::string hash = function_cache.hash_args();
        if(!function_cache.has_value(hash)){
            //Executa bloco da função
            std::visit(walker::VisitTerm{}, term->value.terms.front());
            
            if(function_cache.function_can_have_cache()){
                Type value = _stack.pop();
                function_cache.set_value(hash, value);
                _stack.push(value);
            }
        }
        else{
            Type value = function_cache.get_value(hash);
            _stack.push(value);
        }
        
        function_cache.output_function();

        variable_symbol_table = symbol_table_function->GetParent();
    }

    void run_function_decl(box<Let>& term){
        std::string id = term->name.text;
        //Term value = term->value.terms.front();

        _memory.increment(current_scope + 1);

        rinha_compiler::Symbol symbol = rinha_compiler::init_symbol(id, current_scope, term);

        symbol = variable_symbol_table->Put(id, symbol);

        //Armazena na memória uma tupla com ('nome da função', 'ponteiro pra função na AST')
        tupla function_name_point(std::make_tuple(id, term));
        _memory.store(symbol, function_name_point);
    }

    void load_param_list_in_memory(box<Function>& function){
        auto parameters = function->parameters;

        Type arity = _stack.pop();
        int _arity = std::get<int>(arity);
        if(_arity != parameters.size())
            throw rinha_compiler::RinhaException("Quantidade de parâmetros esperados:" + std::to_string(_arity) +", recebidos: "+ std::to_string(parameters.size()), function->location);

        for (int i = parameters.size() - 1; i >= 0; i--)
        {
            Type value = _stack.pop();
            std::string id = parameters[i].text;
            rinha_compiler::Symbol symbol = rinha_compiler::init_symbol(id, current_scope);

            symbol = variable_symbol_table->Put(id, symbol);

            _memory.store(symbol, value);

            function_cache.push_parameters(value);
        }
    }
    
    Type get_function_callee(box<Call>& term){
        //Recupera informações da função, da memória
        std::visit(walker::VisitTerm{}, term->callee.terms.front());
        Type function_name_point = _stack.pop();

        // if(!std::holds_alternative<box<tupla>>(function_name_point))
        //     throw rinha_compiler::RinhaException("Nome de função inválido.", term->location);
        
        // return std::get<box<tupla>>(function_name_point);
        return function_name_point;
    }

    std::string get_function_name(box<tupla>& function_name_pointer){
        std::string id = std::get<std::string>(std::get<0>(function_name_pointer->value));
        return id;
    }

    Term get_function_pointer(box<tupla>& function_name_pointer){
        Term term = std::get<Term>(std::get<1>(function_name_pointer->value));
        return term;
    }

    void load_arguments_onto_stack(box<Call>& term){
        int arity = term->arguments.terms.size();
        if(arity > 0){
            for(auto arg: term->arguments.terms)
                std::visit(walker::VisitTerm{}, arg);
        }
        _stack.push(arity);
    }

    void create_page_memory(int current_scope){
        //Aloca mas espaço na memória, para o novo escopo
        _memory.increment(current_scope + 1);
        //Cria página de memória
        _memory.push(current_scope);
    }
    void delete_page_memory(int current_scope){
        //Deleta página de memória
        _memory.pop(current_scope);
    }

}