#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <map>
#include <box.hpp>
#include <variant>
#include <daw/json/daw_json_link.h>

//#define TRACE
#if defined(TRACE)
#define trace(msg) std::cout << "TRACE: " <<  msg << std::endl;
#else
#define trace(msg)
#endif

#ifndef AST_HPP
#define AST_HPP

enum class BinaryOp : uint8_t { Add, Sub, Mul, Div, Rem, Eq, Neq, Lt, Gt, Lte, Gte, And, Or };

struct Location
{
    int start = 0;
    int end = 0;
    std::string filename{};
};

struct Str
{
  std::string kind{};
  std::string value{};
  Location location;
};

struct Int
{
  std::string kind{};
  int value;
  Location location;
};

struct Bool
{
  std::string kind{};
  bool value;
  Location location;
};

using Term = std::variant<Int,
                          Str,
                          box<struct Call>,
                          box<struct Binary>,
                          box<struct Function>, 
                          box<struct Let>, 
                          box<struct If>, 
                          box<struct Print>,
                          box<struct First>,
                          box<struct Second>,
                          Bool,
                          box<struct Tuple>,
                          box<struct Var>
                        >;
struct BoxTerm{
  bool is_vector;
  std::vector<Term> terms;
};

struct Print
{
    std::string kind{};
    BoxTerm value;
    Location location;
};

struct Parameter{
  std::string text{};
  Location location;
};

struct Var
{
    std::string kind{};
    std::string text{};
    Location location;
};

struct Function
{
    std::string kind{};
    std::vector<Parameter> parameters;
    BoxTerm value;
    Location location;
};

struct Call
{
    std::string kind{};
    BoxTerm callee;
    BoxTerm arguments;
    Location location;
};

struct Let
{
    std::string kind{};
    Parameter name;
    BoxTerm value;
    BoxTerm next;
    Location location;
};

struct Binary {
  std::string kind{};
  BoxTerm lhs;
  BinaryOp op{};
  BoxTerm rhs;
  Location location;
};

struct If {
  std::string kind{};
  BoxTerm condition;
  BoxTerm then;
  BoxTerm otherwise;
  Location location;
};

struct Tuple {
  std::string kind{};
  BoxTerm first;
  BoxTerm second;
  Location location;
};

struct First
{
    std::string kind{};
    BoxTerm value;
    Location location;
};

struct Second
{
    std::string kind{};
    BoxTerm value;
    Location location;
};


struct File{
  std::string name{};
  BoxTerm expression;
  Location location;
};

#endif