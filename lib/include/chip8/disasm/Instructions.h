//
// Created by rob on 9/5/20.
//

#ifndef CHIP8_DISASSEMBLER_INSTRUCTIONS_H
#define CHIP8_DISASSEMBLER_INSTRUCTIONS_H

#include <variant>
#include <iosfwd>
#include <cstdint>
#include <ostream>

#include "fmt/core.h"

namespace chip8::disasm {

	namespace instruction {

		namespace detail {

			//https://www.fluentcpp.com/2017/05/19/crtp-helper/
			template<typename T>
			struct crtp {
				T &underlying() { return static_cast<T &>(*this); }

				[[nodiscard]] T const &underlying() const { return static_cast<T const &>(*this); }
			};

			template<typename T>
			struct inst_base : crtp<T> {
				std::uint16_t bin;
				std::uint16_t loc;

				inst_base() : bin(0x0000), loc(0) {}

				inst_base(std::uint16_t opcode, std::uint16_t _l) : bin(opcode), loc(_l) {}

				[[nodiscard]] const char *get_mnemonic() const {
					return this->underlying().mnemonic;
				}

				[[nodiscard]] std::string get_c_equiv() const {
					//format string arguments: nnn, x, y, kk, n

					//casts are needed because std::uint8_t is typedef'ed as unsigned char or similar
					//boost format would default-format it as an (unprintable) char before applying formatting
					return fmt::format(this->underlying().cequiv, nnn(), x(), y(), kk(), n());
					/*
					return boost::str(ignore_extra_args(this->underlying().cequiv)
					                  % (unsigned int) nnn()
					                  % (unsigned int) x()
					                  % (unsigned int) y()
					                  % (unsigned int) kk()
					                  % (unsigned int) n());
					                  */
				}

				[[nodiscard]] std::uint16_t nnn() const {
					return bin & 0x0FFFu;
				}

				[[nodiscard]] std::uint8_t x() const {
					return (bin & 0x0F00u) >> 8u;
				}

				[[nodiscard]] std::uint8_t y() const {
					return (bin & 0x00F0u) >> 4u;
				}

				[[nodiscard]] std::uint8_t kk() const {
					return bin & 0x00FFu;
				}

				[[nodiscard]] std::uint8_t n() const {
					return bin & 0x000Fu;
				}
			};
		}

		//0NNN 	Calls machine code routine (RCA 1802 for COSMAC VIP) at address NNN. Not necessary for most ROMs.
		struct SYS : public detail::inst_base<SYS> {
			constexpr static const char *mnemonic{"SYS"};
			//constexpr static const char* description{"Calls machine code routine (RCA 1802 for COSMAC VIP) at address NNN. Not necessary for most ROMs."};
			constexpr static const char *cequiv{"syscall()"};
		};
		//00E0 	Clears the screen.
		struct CLS : public detail::inst_base<CLS> {
			constexpr static const char *mnemonic{"CLS"};
			constexpr static const char *cequiv{"clear_screen()"};
		};
		//00EE 	Returns from a subroutine.
		struct RET : public detail::inst_base<RET> {
			constexpr static const char *mnemonic{"RET"};
			constexpr static const char *cequiv{"return"};
		};
		//1NNN 	Jumps to address NNN.
		struct JUMPI : public detail::inst_base<JUMPI> {
			constexpr static const char *mnemonic{"JUMPI"};
			constexpr static const char *cequiv{"goto %1$#05x"};
		};
		//2NNN 	Calls subroutine at NNN.
		struct CALLI : public detail::inst_base<CALLI> {
			constexpr static const char *mnemonic{"CALLI"};
			constexpr static const char *cequiv{"call %1$#05x"};
		};
		//3XNN 	Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)
		struct SKEI : public detail::inst_base<SKEI> {
			constexpr static const char *mnemonic{"SKEI"};
			constexpr static const char *cequiv{"if (V%2$x == %1$#05x)"};
		};
		//4XNN 	Skips the next instruction if VX doesn't equal NN. (Usually the next instruction is a jump to skip a code block)
		struct SKNEI : public detail::inst_base<SKNEI> {
			constexpr static const char *mnemonic{"SKNEI"};
			constexpr static const char *cequiv{"if (V%2$x != %1$#05x)"};
		};
		//5XY0 	Skips the next instruction if VX equals VY. (Usually the next instruction is a jump to skip a code block)
		struct SKER : public detail::inst_base<SKER> {
			constexpr static const char *mnemonic{"SKER"};
			constexpr static const char *cequiv{"if (V%2$x == V%3$x)"};
		};
		//6XNN 	Sets VX to NN.
		struct SETI : public detail::inst_base<SETI> {
			constexpr static const char *mnemonic{"SETI"};
			constexpr static const char *cequiv{"V%2$x = %5$#03x"};
		};
		//7XNN 	Adds NN to VX. (Carry flag is not changed)
		struct ADDI : public detail::inst_base<ADDI> {
			constexpr static const char *mnemonic{"ADDI"};
			constexpr static const char *cequiv{"V%2$x += %1$#05x"};
		};
		//8XY0 	Sets VX to the value of VY.
		struct SETR : public detail::inst_base<SETR> {
			constexpr static const char *mnemonic{"SETR"};
			constexpr static const char *cequiv{"V%2$x = V%3$x"};
		};
		//8XY1 	Vx=Vx|Vy 	Sets VX to VX or VY. (Bitwise OR operation)
		struct ORR : public detail::inst_base<ORR> {
			constexpr static const char *mnemonic{"ORR"};
			constexpr static const char *cequiv{"V%2$x |= V%3$x"};
		};
		//8XY2 	Vx=Vx&Vy 	Sets VX to VX and VY. (Bitwise AND operation)
		struct ANDR : public detail::inst_base<ANDR> {
			constexpr static const char *mnemonic{"ANDR"};
			constexpr static const char *cequiv{"V%2$x &= V%3$x"};
		};
		//8XY3[a] 	BitOp 	Vx=Vx^Vy 	Sets VX to VX xor VY.
		struct XORR : public detail::inst_base<XORR> {
			constexpr static const char *mnemonic{"XORR"};
			constexpr static const char *cequiv{"V%2$x ^= V%3$x"};
		};
		//8XY4 	Math 	Vx += Vy 	Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
		struct ADDR : public detail::inst_base<ADDR> {
			constexpr static const char *mnemonic{"ADDR"};
			constexpr static const char *cequiv{"V%2$x += V%3$x"};
		};
		//8XY5 	Math 	Vx -= Vy 	VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
		struct SUBR : public detail::inst_base<SUBR> {
			constexpr static const char *mnemonic{"SUBR"};
			constexpr static const char *cequiv{"V%2$x -= V%3$x"};
		};
		//8XY6[a] 	BitOp 	Vx>>=1 	Stores the least significant bit of VX in VF and then shifts VX to the right by 1.[b]
		struct SHR : public detail::inst_base<SHR> {
			constexpr static const char *mnemonic{"SHR"};
			constexpr static const char *cequiv{"V%2$x >>= 1"};
		};
		//8XY7[a] 	Math 	Vx=Vy-Vx 	Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
		struct SUBR_R : public detail::inst_base<SUBR_R> {
			constexpr static const char *mnemonic{"SUBR_R"};
			constexpr static const char *cequiv{"V%2$x = V%3$x - V%2$x"};
		};
		//8XYE[a] 	BitOp 	Vx<<=1 	Stores the most significant bit of VX in VF and then shifts VX to the left by 1.[b]
		struct SHL : public detail::inst_base<SHL> {
			constexpr static const char *mnemonic{"SHL"};
			constexpr static const char *cequiv{"V%2$x <<= 1"};
		};
		//9XY0 	Cond 	if(Vx!=Vy) 	Skips the next instruction if VX doesn't equal VY. (Usually the next instruction is a jump to skip a code block)
		struct SKNER : public detail::inst_base<SKNER> {
			constexpr static const char *mnemonic{"SKNER"};
			constexpr static const char *cequiv{"if (V%2$x != V%3$x)"};
		};
		//ANNN 	MEM 	I = NNN 	Sets I to the address NNN.
		struct ISETI : public detail::inst_base<ISETI> {
			constexpr static const char *mnemonic{"ISETI"};
			constexpr static const char *cequiv{"I = %1$#05x"};
		};
		//BNNN 	Flow 	PC=V0+NNN 	Jumps to the address NNN plus V0.
		struct JUMPIND : public detail::inst_base<JUMPIND> {
			constexpr static const char *mnemonic{"JUMPIND"};
			constexpr static const char *cequiv{"PC = V%2$x + %1$#05x"};
		};
		//CXNN 	Rand 	Vx=rand()&NN 	Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
		struct RAND : public detail::inst_base<RAND> {
			constexpr static const char *mnemonic{"RAND"};
			constexpr static const char *cequiv{"V%2$x = rand() & {3:02X}"};
		};
		//DXYN 	Disp 	draw(Vx,Vy,N) 	Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N+1 pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen
		struct DRAW : public detail::inst_base<DRAW> {
			constexpr static const char *mnemonic{"DRAW"};
			constexpr static const char *cequiv{"draw(V%2$X, V%3$x, %5$#03x)"};
		};
		//EX9E 	KeyOp 	if(key()==Vx) 	Skips the next instruction if the key stored in VX is pressed. (Usually the next instruction is a jump to skip a code block)
		struct SKEK : public detail::inst_base<SKEK> {
			constexpr static const char *mnemonic{"SKEK"};
			constexpr static const char *cequiv{"if (key() == V%2$x)"};
		};
		//EXA1 	KeyOp 	if(key()!=Vx) 	Skips the next instruction if the key stored in VX isn't pressed. (Usually the next instruction is a jump to skip a code block)
		struct SKNEK : public detail::inst_base<SKNEK> {
			constexpr static const char *mnemonic{"SKNEK"};
			constexpr static const char *cequiv{"if (key() != V%2$x)"};
		};
		//FX07 	Timer 	Vx = get_delay() 	Sets VX to the value of the delay timer.
		struct GETD : public detail::inst_base<GETD> {
			constexpr static const char *mnemonic{"GETD"};
			constexpr static const char *cequiv{"V%2$x = get_delay()"};
		};
		//FX0A 	KeyOp 	Vx = get_key() 	A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event)
		struct KEY : public detail::inst_base<KEY> {
			constexpr static const char *mnemonic{"KEY"};
			constexpr static const char *cequiv{"V%2$x = get_key()"};
		};
		//FX15 	Timer 	delay_timer(Vx) 	Sets the delay timer to VX.
		struct SETD : public detail::inst_base<SETD> {
			constexpr static const char *mnemonic{"SETD"};
			constexpr static const char *cequiv{"delay = V%2$x"};
		};
		//FX18 	Sound 	sound_timer(Vx) 	Sets the sound timer to VX.
		struct SETS : public detail::inst_base<SETS> {
			constexpr static const char *mnemonic{"SETS"};
			constexpr static const char *cequiv{"sound = V%2$x"};
		};
		//FX1E 	MEM 	I +=Vx 	Adds VX to I. VF is not affected.[c]
		struct IADDR : public detail::inst_base<IADDR> {
			constexpr static const char *mnemonic{"IADDR"};
			constexpr static const char *cequiv{"I += V%2$x"};
		};
		//FX29 	MEM 	I=sprite_addr[Vx] 	Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
		struct SPRITE : public detail::inst_base<SPRITE> {
			constexpr static const char *mnemonic{"SPRITE"};
			constexpr static const char *cequiv{"I = sprite(V%2$x)"};
		};
		//FX33 	BCD 	set_BCD(Vx);
		//
		//*(I+0)=BCD(3);
		//
		//*(I+1)=BCD(2);
		//
		//*(I+2)=BCD(1);
		//	Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.)
		struct BCD : public detail::inst_base<BCD> {
			constexpr static const char *mnemonic{"BCD"};
			constexpr static const char *cequiv{"BCD()"};
		};
		//FX55 	MEM 	reg_dump(Vx,&I) 	Stores V0 to VX (including VX) in memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.[d]
		struct STORE : public detail::inst_base<STORE> {
			constexpr static const char *mnemonic{"STORE"};
			constexpr static const char *cequiv{"store()"};
		};
		//FX65 	MEM 	reg_load(Vx,&I) 	Fills V0 to VX (including VX) with values from memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.[d]
		struct LOAD : public detail::inst_base<LOAD> {
			constexpr static const char *mnemonic{"LOAD"};
			constexpr static const char *cequiv{"load()"};
		};
	}

	using namespace instruction;
	using Instruction = std::variant<
			SYS, CLS, RET, JUMPI, CALLI, SKEI, SKNEI, SKER, ADDI, SETI, SETR, ORR, ANDR, XORR, ADDR, SUBR, SUBR_R,
			SHR, SHL, SKNER, ISETI, JUMPIND, RAND, DRAW, SKEK, SKNEK, GETD, KEY, SETD, SETS, IADDR, SPRITE, BCD, STORE,
			LOAD
	>;


}

#endif //CHIP8_DISASSEMBLER_INSTRUCTIONS_H
