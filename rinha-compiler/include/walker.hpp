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
        void operator()(Int& term){  run_int(term);}
        void operator()(Str& term){  run_str(term);}
        void operator()(box<Call>& term){  run_call(term);}
        void operator()(box<Binary>& term){  run_binary(term);}
        void operator()(box<Function>& term){  run_function(term);}
        void operator()(box<Let>& term){  run_let(term);}
        void operator()(box<If>& term){  run_if(term);}
        void operator()(box<Print>& term){  run_print(term);}
        void operator()(box<First>& term){  run_first(term);}
        void operator()(box<Second>& term){  run_second(term);}
        void operator()(Bool& term){  run_bool(term);}
        void operator()(box<Tuple>& term){  run_tuple(term);}
        void operator()(box<Var>& term){  run_var(term);}
    };


}

#endif