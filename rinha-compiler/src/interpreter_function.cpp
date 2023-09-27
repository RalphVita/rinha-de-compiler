#include <interpreter.hpp>
#include <walker.hpp>
#include <rinha_exception.hpp>
#include <type.hpp>
#include <interpreter_function.hpp>

extern rinha_compiler::stack _stack;
extern rinha_compiler::Memory _memory;
extern rinha_compiler::SymbolTable* symbolTable;
extern int current_scope;

namespace rinha_compiler::walker {
    void run_call(box<Call>& term){
        int saved_scope = current_scope;

        //Carrega argumentos na pilha
        int arity = term->arguments.terms.size();
        if(arity > 0){
            for(auto arg: term->arguments.terms)
                std::visit(walker::VisitTerm{}, arg);
        }

        //Recupera nome da função
        std::visit(walker::VisitTerm{}, term->callee.terms.front());
        Type function_name = _stack.pop();
        if(!std::holds_alternative<std::string>(function_name))
            throw rinha_compiler::RinhaException("Nome de função inválido.", term->location);
        
        //Recupera função da tabela de simbolos
        std::string id = std::get<std::string>(function_name);
        rinha_compiler::Symbol symbol = symbolTable->Get(id);
        
        //Muda de escopo
        //A função sempre é salva com o espopo da parent. Então o novo escopo é:
        current_scope = symbol.scope + 1;

        //Aloca mas espaço na memória, para o novo escopo
        _memory.increment(current_scope + 1);
        //Cria página de memória
        _memory.push(current_scope);
        
        //Busca e aponta para o bloco da função na AST
        auto let_function = std::get<box<Let>>(symbol.term);

        //Varre o bloco da função recursivamente
        std::visit(walker::VisitTerm{}, let_function->value.terms.front());

        //Deleta página de memória
        _memory.pop(current_scope);

        current_scope = saved_scope;
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

}