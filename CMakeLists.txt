cmake_minimum_required(VERSION 3.22.1)
project(rinha "CXX")



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

enable_testing()

add_subdirectory(tests)

find_package( daw-json-link )

file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(rinha ${sources})

add_library(rinha2 SHARED "${CMAKE_CURRENT_SOURCE_DIR}/src/parser_json_to_ast.cpp")
target_include_directories(rinha2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(rinha PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")



target_link_libraries(rinha daw::daw-json-link )