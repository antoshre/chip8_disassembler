cmake_minimum_required(VERSION 3.15)
project(chip8_disassembler_lib)

add_subdirectory(external)

add_library(${PROJECT_NAME} src/BinFile.cpp src/parser.cpp src/Listing.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE src PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE cppitertools::cppitertools ${Boost_LIBRARIES})

add_library(chip8::disasm ALIAS ${PROJECT_NAME})

