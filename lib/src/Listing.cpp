//
// Created by rob on 9/5/20.
//
#include <iomanip>
#include <iostream>

#include "chip8/disasm/Listing.h"
#include "chip8/disasm/parser/parser.h"
#include "chip8/disasm/BinFile.h"

#include "chunked.hpp"

namespace chip8::disasm {
	Listing::Listing(const BinFile &bin) {
		const auto &binary = bin.bin();

		std::uint16_t location = 0x200;

		for (auto &&chunk : iter::chunked(binary, 2)) {
			std::uint16_t opcode = (chunk[0] << 8u) | chunk[1];
			Instruction inst;
			try {
				inst = parser::parse(opcode, location++);
			} catch (std::runtime_error &e) {
				//std::cerr << "Failed to parse word: ";
				//std::cerr << std::hex << std::uppercase << std::setw(4) << std::setfill('0') <<  opcode << std::endl;
				//Assume we have hit the end of instructions, the rest of is data
				break;
			}
			instructions.push_back(inst);
		}
	}

	std::ostream &operator<<(std::ostream &os, const Listing &obj) {
		os << "Listing:\n";
		for (const Instruction &inst : obj.instructions) {
			std::visit([&os](auto &&i) {
				os << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << i.bin << ": ";
				os << i.get_mnemonic() << "\t| " << i.get_c_equiv();
			}, inst);
			os << '\n';
		}
		return os;
	}
}