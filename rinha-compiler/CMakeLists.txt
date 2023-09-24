cmake_minimum_required(VERSION 3.22.1)
project(rinha-compiler "CXX")

find_package(daw-json-link)

include_directories(include)

file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library( ${PROJECT_NAME} SHARED "${CMAKE_CURRENT_SOURCE_DIR}/src/symbol.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/symbol_table.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/parser_json_to_ast.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/interpreter.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/compiler.cpp")
target_include_directories( ${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
#add_executable(rinha-compiler ${sources})

# add_library(rinha2 SHARED "${CMAKE_CURRENT_SOURCE_DIR}/src/parser_json_to_ast.cpp")
# target_include_directories(rinha2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# target_include_directories(rinha-compile PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries( rinha-compiler PUBLIC daw::daw-json-link )
#target_link_libraries(rinha-compiler PUBLIC include )