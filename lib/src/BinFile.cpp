//
// Created by rob on 9/5/20.
//

#include "chip8/disasm/BinFile.h"

#include <iomanip>
#include <cstdio>

#include "chunked.hpp"


namespace chip8::disasm {

	BinFile::BinFile(std::istream &f) : BinFile(std::istreambuf_iterator<char>(f)) {}

	BinFile::BinFile(const std::istreambuf_iterator<char> &iter) : binary(iter, std::istreambuf_iterator<char>()) {}

	[[nodiscard]] const std::vector<std::uint8_t> &BinFile::bin() const {
		return std::as_const(binary);
	}

	std::ostream &operator<<(std::ostream &os, const BinFile &obj) {
		os << "BinFile[";
		if (!obj.binary.empty()) {
			for (int i = 0; i < obj.binary.size() - 1; i++) {
				std::printf("%02hhX ", obj.binary[i]);
			}
			auto last_elem = obj.binary.end() - 1;
			std::printf("%02hhX", *last_elem);
		}
		os << "]";
		return os;
	}
}