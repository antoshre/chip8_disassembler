//
// Created by rob on 9/5/20.
//

#ifndef CHIP8_DISASSEMBLER_PARSER_H
#define CHIP8_DISASSEMBLER_PARSER_H

#include "../Instructions.h"

namespace chip8::disasm::parser {
	Instruction parse(std::uint16_t);
}

#endif //CHIP8_DISASSEMBLER_PARSER_H
