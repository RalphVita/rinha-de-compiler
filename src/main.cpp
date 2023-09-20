#include "box.hpp"
#include "ast.hpp"
#include <daw/json/daw_json_link.h>

#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <map>
#include <variant>


using TermMaker2 = struct TermMaker;

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
  struct json_data_contract<Print> {
    using type =
      json_member_list<
        json_string<"kind">, 
        //json_string<"value">, 
        //json_class<"value", Str>,
        json_raw<"value", Term, TermMaker2>,
        json_class<"location", Location>
      >;
  };

};




struct TermMaker {
    Term operator( )( char const *str, std::size_t sz ) const {
        using namespace daw::json;
		auto jv = json_value( daw::string_view( str, sz ) );
		(void)jv;
        Term t;
        bool compare = jv["kind"].get_string().compare("Print") == 0;
        switch( compare  ) {
            case true:
                t = from_json<Print>( jv ); 
            break;
            case false:
                t = std::move(from_json<Str>( jv ));
            break;
            default:
                std::terminate();
        }
        return t;	
	}
};

namespace daw::json {
  template <> 
  struct json_data_contract<File> {
    using type =
      json_member_list<
        json_string<"name">, 
        json_raw<"expression", Term, TermMaker>,
        json_class<"location", Location>
      >;
  };
}

using Type = std::variant<int, bool, std::string>;

struct VisitTerm {
    Type operator()(box<Print>& term){ 
      Type value = std::visit(*this, term->value);
      std::visit([](const auto &x) { std::cout << x << std::endl; }, value);
      return value;
    }
    Type operator()(Str& term)       { return term.value;}
};

int main() {
    std::string_view test_001_t_json_data = R"({
    "name": "print.rinha",
    "expression": {
        "kind": "Print",
        "value": {
        "value": "Hello world",
        "kind": "Str",
        
        "location": {
            "start": 7,
            "end": 20,
            "filename": "print.rinha"
        }
        },
        "location": {
        "start": 0,
        "end": 21,
        "filename": "print.rinha"
        }
    },
    "location": {
        "start": 0,
        "end": 21,
        "filename": "print.rinha"
    }
    })";
    
    
    File file = daw::json::from_json<File>(test_001_t_json_data);

    std::visit(VisitTerm{}, file.expression);
}