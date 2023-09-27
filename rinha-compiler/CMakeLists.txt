cmake_minimum_required(VERSION 3.0)
project(rinha-compiler "CXX")

include( FetchContent )
FetchContent_Declare(
  daw_json_link
  GIT_REPOSITORY https://github.com/beached/daw_json_link
  GIT_TAG release
)
FetchContent_MakeAvailable(daw_json_link)

include_directories(include)

add_library(${PROJECT_NAME} 
                SHARED 
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/box.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/type.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/ast.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/rinha_exception.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/symbol.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/symbol_table.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/memory.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/stack.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/parser_json_to_ast.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/walker.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/interpreter.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/interpreter_function.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/interpreter_binary_operation.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/compiler.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/stack.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/rinha_exception.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/symbol.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/memory.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/symbol_table.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/parser_json_to_ast.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/interpreter_binary_operation.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/interpreter_function.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/interpreter_walker.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/interpreter.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/compiler.cpp"
            )
target_include_directories(${PROJECT_NAME} 
                                PUBLIC 
                                    "${CMAKE_CURRENT_SOURCE_DIR}/include"
                            )

target_link_libraries(rinha-compiler PUBLIC daw::daw-json-link)