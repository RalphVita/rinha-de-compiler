cmake_minimum_required(VERSION 3.22.1)
project(rinha-compiler "CXX")

find_package(daw-json-link)


include_directories(include)

file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${sources})
#add_executable(rinha-compiler ${sources})

# add_library(rinha2 SHARED "${CMAKE_CURRENT_SOURCE_DIR}/src/parser_json_to_ast.cpp")
# target_include_directories(rinha2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# target_include_directories(rinha-compile PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(rinha-compiler daw::daw-json-link )