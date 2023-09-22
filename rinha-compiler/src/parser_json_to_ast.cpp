#include <parser_json_to_ast.hpp>
#include <daw/json/daw_json_link.h>
#include <variant>
namespace json_to_ast {
using TermMaker2 = struct TermMaker;
using VectorTermMaker = struct _VectorTermMaker;
}


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
        json_raw<"value", Term, json_to_ast::TermMaker2>,
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
        json_raw<"value", Term, json_to_ast::TermMaker2>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Call> {
    using type =
      json_member_list<
        json_string<"kind">,
        json_raw<"callee", Term, json_to_ast::TermMaker2>,
        json_raw<"arguments", std::vector<Term>, json_to_ast::VectorTermMaker>, 
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Let> {
    using type =
      json_member_list<
        json_string<"kind">,
        json_class<"name", Parameter>,
        json_raw<"value", Term, json_to_ast::TermMaker2>,
        json_raw<"next", Term, json_to_ast::TermMaker2>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Binary> {
    using type =
      json_member_list<
        json_string<"kind">,
        json_raw<"lhs", Term, json_to_ast::TermMaker2>,
        json_string<"op">,
        json_raw<"rhs", Term, json_to_ast::TermMaker2>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<If> {
    using type =
      json_member_list<
        json_string<"kind">,
        json_raw<"condition", Term, json_to_ast::TermMaker2>,
        json_raw<"then", Term, json_to_ast::TermMaker2>,
        json_raw<"otherwise", Term, json_to_ast::TermMaker2>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Tuple> {
    using type =
      json_member_list<
        json_string<"kind">,
        json_raw<"first", Term, json_to_ast::TermMaker2>,
        json_raw<"second", Term, json_to_ast::TermMaker2>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<Second> {
    using type =
      json_member_list<
        json_string<"kind">, 
        json_raw<"value", Term, json_to_ast::TermMaker2>,
        json_class<"location", Location>
      >;
  };

  template <> 
  struct json_data_contract<First> {
    using type =
      json_member_list<
        json_string<"kind">, 
        json_raw<"value", Term, json_to_ast::TermMaker2>,
        json_class<"location", Location>
      >;
  };

};

namespace json_to_ast {


struct _VectorTermMaker{
  std::vector<Term> operator( )( char const *str, std::size_t sz )  {
    using namespace daw::json;
    auto json_data = daw::string_view( str, sz );
    auto jv = json_value( daw::string_view( str, sz ) );

    auto jv2 = json_value( daw::string_view( jv[0].get_string() ) );
	(void)jv2;
  std::vector<Term> terms;
  Term term;

    std::cout << json_data << std::endl;

    
    //std::cout << jv.begin().value().get_string() << std::endl;
    std::cout << jv[0].get_string() << std::endl;




    
  std::string kind = jv2["kind"].get_string();
  std::cout << kind << std::endl;
  
  if(kind == "Int")
    term = std::move(from_json<Int>( jv2 ));
  else if(kind == "Str")
    term = std::move(from_json<Str>( jv2 ));
  // else if(kind == "Call")
  //   term = from_json<Call>( jv );
  // else if(kind == "Binary")
  //   term = from_json<Binary>( jv2 );
  // else if(kind == "Function")
  //   term = from_json<Function>( jv );
  // else if(kind == "Let")
  //   term = from_json<Let>( jv );
  // else if(kind == "If")
  //   term = from_json<If>( jv );
  // else if(kind == "Print")
  //   term = from_json<Print>( jv );
  // else if(kind == "First")
  //   term = from_json<First>( jv );
  // else if(kind == "Second")
  //   term = from_json<Second>( jv );
  // else if(kind == "Bool")
  //   term = std::move(from_json<Bool>( jv ));
  // else if(kind == "Tuple")
  //   term = from_json<Tuple>( jv );
  // else if(kind == "Var")
  //   term = from_json<Var>( jv );
  else{
    std::cout << "Kind Invalido TODO" << std::endl;
    std::terminate();
  }
  terms.push_back(term);
  return terms;

    
    //std::vector<Binary> termf = daw::json::from_json_array<Binary, std::vector<Binary>>( daw::string_view( str, sz ) );
    
    //std::cout << termf.size() << std::endl;
    //std::vector<Term> term;
    //return term;
  }
  // Arguments operator( )( char const *str, std::size_t sz ) const {
   
  //       //using namespace daw::json;
  //       Arguments terms; //= daw::json::from_json_array<Term, std::vector<Term>, TermMaker>( daw::string_view( str, sz ) );
  //       terms.arguments = "OI";
  //       return terms;
	// }
};

struct TermMaker {
  Term operator( )( char const *str, std::size_t sz )  {
    //using namespace json_to_ast;
  using namespace daw::json;
  //using namespace 
  //std::cout << str << std::endl;
	auto jv = json_value( daw::string_view( str, sz ) );
	(void)jv;
  Term term;
  std::string kind = jv["kind"].get_string();
  std::cout << kind << std::endl;
  
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
	}
};



}


namespace daw::json {
  template <> 
  struct json_data_contract<File> {
    using type =
      json_member_list<
        json_string<"name">, 
        json_raw<"expression", Term, json_to_ast::TermMaker>,
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