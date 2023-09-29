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


namespace rinha_compiler::interpreter {

    void walk(File file){
        current_scope = 0;
        _memory.increment(current_scope + 1);
        _memory.push(current_scope);
        variable_symbol_table = new rinha_compiler::SymbolTable();
        std::visit(walker::VisitTerm{}, file.expression.terms.front());
    }
}
