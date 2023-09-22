#include <parser_json_to_ast.hpp>
#include <daw/json/daw_json_link.h>
#include <variant>

using BoxTermMaker = struct _BoxTermMaker;


namespace daw::json {
  

  template <> 
  struct json_data_contract<Location> {
    using type =
      json_member_list<
        json_number<"start", int>,
        json_number<"end", int>,
        json_string<"filename"> 
      >;
  };


template <> 
  struct json_data_contract<Str> {
    using type =
      json_member_list<
        json_string<"kind">, 
        json_string<"value">,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Int> {
    using type =
      json_member_list<
        json_string<"kind">, 
        json_number<"value", int>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Bool> {
    using type =
      json_member_list<
        json_string<"kind">, 
        json_bool<"value">,
        json_class<"location", Location>
      >;
  };

  
  template <> 
  struct json_data_contract<Print> {
    using type =
      json_member_list<
        json_string<"kind">, 
        json_raw<"value", BoxTerm, BoxTermMaker>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Parameter> {
    using type =
      json_member_list<
        json_string<"text">, 
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Var> {
    using type =
      json_member_list<
        json_string<"kind">,
        json_string<"text">, 
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Function> {
    using type =
      json_member_list<
        json_string<"kind">,
        json_array<"parameters", Parameter>, 
        json_raw<"value", BoxTerm, BoxTermMaker>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Call> {
    using type =
      json_member_list<
        json_string<"kind">,
        json_raw<"callee", BoxTerm, BoxTermMaker>,
        json_raw<"arguments", BoxTerm, BoxTermMaker>, 
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Let> {
    using type =
      json_member_list<
        json_string<"kind">,
        json_class<"name", Parameter>,
        json_raw<"value", BoxTerm, BoxTermMaker>,
        json_raw<"next", BoxTerm, BoxTermMaker>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Binary> {
    using type =
      json_member_list<
        json_string<"kind">,
        json_raw<"lhs", BoxTerm, BoxTermMaker>,
        json_string<"op">,
        json_raw<"rhs", BoxTerm, BoxTermMaker>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<If> {
    using type =
      json_member_list<
        json_string<"kind">,
        json_raw<"condition", BoxTerm, BoxTermMaker>,
        json_raw<"then", BoxTerm, BoxTermMaker>,
        json_raw<"otherwise", BoxTerm, BoxTermMaker>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Tuple> {
    using type =
      json_member_list<
        json_string<"kind">,
        json_raw<"first", BoxTerm, BoxTermMaker>,
        json_raw<"second", BoxTerm, BoxTermMaker>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Second> {
    using type =
      json_member_list<
        json_string<"kind">, 
        json_raw<"value", BoxTerm, BoxTermMaker>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<First> {
    using type =
      json_member_list<
        json_string<"kind">, 
        json_raw<"value", BoxTerm, BoxTermMaker>,
        json_class<"location", Location>
      >;
  };

};

struct _BoxTermMaker{
  BoxTerm operator( )( char const *str, std::size_t sz ) const {
      using namespace daw::json;
      auto json_data = daw::string_view( str, sz );
      auto jv = json_value(json_data);
      BoxTerm boxTerm;

      auto FactoryTerm = [](daw::json::json_value jv){
                                using namespace daw::json;
                                Term term;
                                std::string kind = jv["kind"].get_string();
                                if(kind == "Int")
                                  term = std::move(from_json<Int>( jv ));
                                else if(kind == "Str")
                                  term = std::move(from_json<Str>( jv ));
                                else if(kind == "Call")
                                  term = from_json<Call>( jv );
                                else if(kind == "Binary")
                                  term = from_json<Binary>( jv );
                                else if(kind == "Function")
                                  term = from_json<Function>( jv );
                                else if(kind == "Let")
                                  term = from_json<Let>( jv );
                                else if(kind == "If")
                                  term = from_json<If>( jv );
                                else if(kind == "Print")
                                  term = from_json<Print>( jv );
                                else if(kind == "First")
                                  term = from_json<First>( jv );
                                else if(kind == "Second")
                                  term = from_json<Second>( jv );
                                else if(kind == "Bool")
                                  term = std::move(from_json<Bool>( jv ));
                                else if(kind == "Tuple")
                                  term = from_json<Tuple>( jv );
                                else if(kind == "Var")
                                  term = from_json<Var>( jv );
                                else{
                                  std::cout << "Kind Invalido TODO" << std::endl;
                                  std::terminate();
                                }

                                return term;
                            };

      if(jv.is_array()){
          boxTerm.is_vector = true;
          int i = 0;
          for (auto jv_item = jv.begin(); jv_item != jv.end(); ++jv_item){
              json_value j_value = jv.find_element(i);
              boxTerm.terms.push_back(FactoryTerm(j_value)); 
              i++;
          }
      }
      else{
          boxTerm.is_vector = false;
          boxTerm.terms.push_back(FactoryTerm(jv));
          
      }

      return boxTerm;
  }
};

namespace daw::json {
  template <> 
  struct json_data_contract<File> {
    using type =
      json_member_list<
        json_string<"name">, 
        json_raw<"expression", BoxTerm, BoxTermMaker>,
        json_class<"location", Location>
      >;
  };
}

namespace json_to_ast {
    File parser(std::string_view json_data){
        File file = daw::json::from_json<File>(json_data);
        return file;
    }
}