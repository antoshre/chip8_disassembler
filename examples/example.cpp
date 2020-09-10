//
// Created by rob on 9/3/20.
//struct

#include <iostream>
#include <fstream>
#include <ranges>


#include "chip8/disasm.h"

using namespace chip8::disasm;

int main() {
	std::ifstream file("../../examples/call.chip8", std::ios::binary | std::ios::in);
	if (!file.is_open()) {
		std::cerr << "Can't open file\n";
		return 1;
	}
	std::istreambuf_iterator<char> iter(file);

	BinFile f(iter);
}