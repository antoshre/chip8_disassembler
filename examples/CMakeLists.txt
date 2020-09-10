cmake_minimum_required(VERSION 3.10)
project(examples)

add_executable(example example.cpp)
target_link_libraries(example chip8::disassembler)

add_executable(parse_to_ast parse_to_ast.cpp)
target_link_libraries(parse_to_ast chip8::disassembler)
