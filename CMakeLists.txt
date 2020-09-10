cmake_minimum_required(VERSION 3.15)
project(chip8_disassembler)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)

option(BUILD_EXAMPLES "Build examples" OFF)
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_EXAMPLES)
	add_subdirectory(examples)
endif ()

option(BUILD_TESTING "Build tests" OFF)
option(ENABLE_COVERAGE "Generate coverage statistics" OFF)
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif ()