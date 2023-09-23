#include "ast.hpp"

#ifndef WALKER_HPP
#define WALKER_HPP

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

namespace walker {
    //using Type = std::variant<int, bool, std::string>;
    
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


}

#endif