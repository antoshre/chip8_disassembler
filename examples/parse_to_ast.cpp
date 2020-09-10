//
// Created by rob on 9/5/20.
//

#include <fstream>
#include <iostream>

#include "chip8/disasm.h"

int main(int argc, char **argv) {

	if (argc != 2) {
		std::cerr << "Usage: [filename]\n";
		return 1;
	}

	std::ifstream file(argv[1], std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Cannot open file: " << argv[1] << '\n';
		return 2;
	}
	//chip8::disasm::BinFile f{file};

	chip8::disasm::Listing list(file);

	std::cout << list << std::endl;
}