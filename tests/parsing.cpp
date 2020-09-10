//
// Created by rob on 9/9/20.
//

#include "chip8/disasm.h"

using namespace chip8::disasm;

#include "gtest/gtest.h"

template<typename T>
bool is(const Instruction &i) {
	return std::holds_alternative<T>(i);
}

TEST(Parsing, Basic) {
	Instruction i;
	i = parser::parse(0x0FFF);
	EXPECT_TRUE(is<SYS>(i));

	i = parser::parse(0x00E0);
	EXPECT_TRUE(is<CLS>(i));

	i = parser::parse(0x00EE);
	EXPECT_TRUE(is<RET>(i));

	i = parser::parse(0x1FFF);
	EXPECT_TRUE(is<JUMPI>(i));

	i = parser::parse(0x2FFF);
	EXPECT_TRUE(is<CALLI>(i));

	i = parser::parse(0x3FFF);
	EXPECT_TRUE(is<SKEI>(i));

	i = parser::parse(0x4FFF);
	EXPECT_TRUE(is<SKNEI>(i));

	i = parser::parse(0x5FF0);
	EXPECT_TRUE(is<SKER>(i));

	i = parser::parse(0x6FFF);
	EXPECT_TRUE(is<SETI>(i));

	i = parser::parse(0x7FFF);
	EXPECT_TRUE(is<ADDI>(i));

	i = parser::parse(0xFF55);
	EXPECT_TRUE(is<STORE>(i));

	//TODO: finish basic tests
}