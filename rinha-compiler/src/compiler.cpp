#include <compiler.hpp>
//#include <walker.hpp>

namespace rinha_compiler::compiler{
    //using VisitTerm = struct _VisitTerm;
    void run_int(Int&);
    void run_str(Str&);
    void run_call(box<Call>&);
    void run_binary(box<Binary>&);
    void run_function(box<Function>&);
    void run_let(box<Let>&);
    void run_if(box<If>&);
    void run_print(box<Print>&);
    void run_first(box<First>&);
    void run_second(box<Second>&);
    void run_bool(Bool&);
    void run_tuple(box<Tuple>&);
    void run_var(box<Var>&);

    struct VisitTerm {
        void operator()(Int& term){  trace("run_int");run_int(term);}
        void operator()(Str& term){  trace("run_str");run_str(term);}
        void operator()(box<Call>& term){  trace("run_call");run_call(term);}
        void operator()(box<Binary>& term){  trace("run_binary");run_binary(term);}
        void operator()(box<Function>& term){  trace("run_function");run_function(term);}
        void operator()(box<Let>& term){  trace("run_let");run_let(term);}
        void operator()(box<If>& term){  trace("run_if");run_if(term);}
        void operator()(box<Print>& term){  trace("run_print");run_print(term);}
        void operator()(box<First>& term){  trace("run_first");run_first(term);}
        void operator()(box<Second>& term){  trace("run_second");run_second(term);}
        void operator()(Bool& term){  trace("run_bool");run_bool(term);}
        void operator()(box<Tuple>& term){  trace("run_tuple");run_tuple(term);}
        void operator()(box<Var>& term){  trace("run_var");run_var(term);}
    };

    void run_int(Int& term){//TODO: Implement
    }
    void run_str(Str& term){
        std::cout << term.value;
    }
    void run_call(box<Call>& term){//TODO: Implement
    }
    void run_binary(box<Binary>& term){//TODO: Implement
    }
    void run_function(box<Function>& term){//TODO: Implement
    }
    void run_let(box<Let>& term){//TODO: Implement
    }
    void run_if(box<If>& term){//TODO: Implement
    }
    void run_print(box<Print>& term){
        std::string print_command = "std::cout << ";
        std::cout << "std::cout << ";
        std::visit(VisitTerm{}, term->value.terms.front());
        std::cout << " << std::endl;" << std::endl;
    }
    void run_first(box<First>& term){//TODO: Implement
    }
    void run_second(box<Second>& term){//TODO: Implement
    }
    void run_bool(Bool& term){//TODO: Implement
    }
    void run_tuple(box<Tuple>& term){//TODO: Implement
    }
    void run_var(box<Var>& term){//TODO: Implement
    }

    

    void walk(File file){
        std::visit(VisitTerm{}, file.expression.terms.front());
    }
}