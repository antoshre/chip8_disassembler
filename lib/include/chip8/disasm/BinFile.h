//
// Created by rob on 9/5/20.
//

#ifndef CHIP8_DISASSEMBLER_BINFILE_H
#define CHIP8_DISASSEMBLER_BINFILE_H

#include <istream>
#include <iosfwd>
#include <cstdint>
#include <vector>

namespace chip8::disasm {
	class BinFile {
		std::vector<std::uint8_t> binary;

	public:
		BinFile(std::istream &f);

		BinFile(const std::istreambuf_iterator<char> &iter);

		friend std::ostream &operator<<(std::ostream &os, const BinFile &obj);

		[[nodiscard]] const std::vector<std::uint8_t> &bin() const;
	};
}

#endif //CHIP8_DISASSEMBLER_BINFILE_H
