# chip8_disassembler
Chip8 Disassembler
Disassembles Chip8 binaries.  Meant to be directly consumed by another project.

Creates target `chip8::disasm`.

## Building
Building examples and tests:
```
mkdir build
cd build
cmake -DBUILD_EXAMPLES=ON -DBUILD_TESTING=ON .
#Run example
examples/parse_to_ast ../roms/all_instructions.ch8
#Run GTest suite 
tests/all_tests
```

## Usage:
```
> parse_to_ast "Chip8 Picture.ch8"

Listing:
00E0: CLS	| clear_screen()
A248: ISETI	| I = 0x248
6000: SETI	| V0 = 000
611E: SETI	| V1 = 0xe
6200: SETI	| V2 = 000
D202: DRAW	| draw(V2, V0, 0x2)
D212: DRAW	| draw(V2, V1, 0x2)
7208: ADDI	| V2 += 0x208
3240: SKEI	| if (V2 == 0x240)
120A: JUMPI	| goto 0x20a
6000: SETI	| V0 = 000
613E: SETI	| V1 = 0xe
6202: SETI	| V2 = 0x2
A24A: ISETI	| I = 0x24a
D02E: DRAW	| draw(V0, V2, 0xe)
D12E: DRAW	| draw(V1, V2, 0xe)
720E: ADDI	| V2 += 0x20e
D02E: DRAW	| draw(V0, V2, 0xe)
D12E: DRAW	| draw(V1, V2, 0xe)
A258: ISETI	| I = 0x258
600B: SETI	| V0 = 0xb
6108: SETI	| V1 = 0x8
D01F: DRAW	| draw(V0, V1, 0xf)
700A: ADDI	| V0 += 0x00a
A267: ISETI	| I = 0x267
D01F: DRAW	| draw(V0, V1, 0xf)
700A: ADDI	| V0 += 0x00a
A276: ISETI	| I = 0x276
D01F: DRAW	| draw(V0, V1, 0xf)
7003: ADDI	| V0 += 0x003
A285: ISETI	| I = 0x285
D01F: DRAW	| draw(V0, V1, 0xf)
700A: ADDI	| V0 += 0x00a
A294: ISETI	| I = 0x294
D01F: DRAW	| draw(V0, V1, 0xf)
1246: JUMPI	| goto 0x246
```
