//
// Created by rob on 9/5/20.
//

#ifndef CHIP8_DISASSEMBLER_LISTING_H
#define CHIP8_DISASSEMBLER_LISTING_H

#include "Instructions.h"

#include <vector>

namespace chip8::disasm {
	class BinFile;

	class Listing {
		std::vector<Instruction> listing;
	public:
		explicit Listing(const BinFile &bin);

		friend std::ostream &operator<<(std::ostream &os, const Listing &obj);
	};
}

#endif //CHIP8_DISASSEMBLER_LISTING_H
