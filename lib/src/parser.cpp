//
// Created by rob on 9/5/20.
//
#include <cstdint>
#include <stdexcept>

#include "chip8/disasm/Instructions.h"

namespace chip8::disasm::parser {

	Instruction parse(std::uint16_t val) {
		using namespace chip8::disasm::instruction;
		std::uint8_t nibbles[4];
		nibbles[0] = (val & 0xF000u) >> 12u;
		nibbles[1] = (val & 0x0F00u) >> 8u;
		nibbles[2] = (val & 0x00F0u) >> 4u;
		nibbles[3] = (val & 0x000Fu);

		switch (nibbles[0]) {
			case 0:
				switch (nibbles[1]) {
					case 0:
						switch (nibbles[3]) {
							case 0:
								return CLS{val};
							case 0xE:
								return RET{val};
						}
					default:
						return SYS{val};
				}
			case 1:
				return JUMPI{val};
			case 2:
				return CALLI{val};
			case 3:
				return SKEI{val};
			case 4:
				return SKNEI{val};
			case 5:
				return SKER{val};
			case 6:
				return SETI{val};
			case 7:
				return ADDI{val};
			case 8:
				switch (nibbles[3]) {
					case 0:
						return SETR{val};
					case 1:
						return ORR{val};
					case 2:
						return ANDR{val};
					case 3:
						return XORR{val};
					case 4:
						return ADDR{val};
					case 5:
						return SUBR{val};
					case 6:
						return SHR{val};
					case 7:
						return SUBR_R{val};
					case 0xE:
						return SHL{val};
				}
			case 9:
				return SKNER{val};
			case 0xA:
				return ISETI{val};
			case 0xB:
				return JUMPIND{val};
			case 0xC:
				return RAND{val};
			case 0xD:
				return DRAW{val};
			case 0xE:
				switch ((nibbles[2] << 4u) | nibbles[3]) {
					case 0x9E:
						return SKEK{val};
					case 0xA1:
						return SKNEK{val};
					default:
						throw std::runtime_error("Unknown instruction");
				}
			case 0xF:
				switch ((nibbles[2] << 4u) | nibbles[3]) {
					case 0x07:
						return GETD{val};
					case 0x0A:
						return KEY{val};
					case 0x15:
						return SETD{val};
					case 0x18:
						return SETS{val};
					case 0x1E:
						return IADDR{val};
					case 0x29:
						return SPRITE{val};
					case 0x33:
						return BCD{val};
					case 0x55:
						return STORE{val};
					case 0x65:
						return LOAD{val};
				}
		}
		throw std::runtime_error("Unknown instruction");
	}
}