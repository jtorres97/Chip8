#include "CPU.h"
#include "Display.h"
#include "Memory.h"
#include "Keyboard.h"

namespace chip8
{
	CPU::CPU(Memory& memory, Display& display, Keyboard& keyboard): memory(memory), display(display),
	                                                                keyboard(keyboard), I(0), PC(0), delayTimer(0),
	                                                                soundTimer(0), SP(0), dist(0, 255)
	{
		std::random_device rd;
		engine = std::mt19937(rd());

		instructions = {
			{
				&CPU::OP_Misc, &CPU::OP_1nnn, &CPU::OP_2nnn, &CPU::OP_3xnn,
				&CPU::OP_4xnn, &CPU::OP_5xy0, &CPU::OP_6xnn, &CPU::OP_7xnn,
				&CPU::OP_Arith, &CPU::OP_9xy0, &CPU::OP_annn, &CPU::OP_bnnn,
				&CPU::OP_cxnn, &CPU::OP_dxyn, &CPU::OP_Key, &CPU::OP_Special
			}
		};

		arithmetic = {
			{
				&CPU::OP_8xy0, &CPU::OP_8xy1, &CPU::OP_8xy2, &CPU::OP_8xy3,
				&CPU::OP_8xy4, &CPU::OP_8xy5, &CPU::OP_8xy6, &CPU::OP_8xy7,
				&CPU::OP_8xye
			}
		};

		special = {
			{0x7, &CPU::OP_fx07}, {0xa, &CPU::OP_fx0a}, {0x15, &CPU::OP_fx15},
			{0x18, &CPU::OP_fx18}, {0x1e, &CPU::OP_fx1e}, {0x29, &CPU::OP_fx29},
			{0x33, &CPU::OP_fx33}, {0x55, &CPU::OP_fx55}, {0x65, &CPU::OP_fx65}
		};
	}

	void CPU::Execute()
	{
		const uint16_t opcode = Fetch();
		const uint8_t index = (opcode >> 12) & 0xF;

		(this->*instructions[index])(opcode);
	}

	void CPU::UpdateTimers()
	{
		if (delayTimer)
		{
			delayTimer--;
		}
		if (soundTimer)
		{
			soundTimer--;
		}
	}

	void CPU::Reset()
	{
		stack.fill(0);
		V.fill(0);
		I = 0;
		PC = Memory::ProgramStart();
		SP = 0;
		delayTimer = 0;
		soundTimer = 0;
	}

	uint16_t CPU::Fetch()
	{
		// Opcodes are stored in Big-Endian notation
		const uint16_t opcode = (static_cast<uint16_t>(memory[PC]) << 8) | memory[PC + 1];

		PC += 2;

		return opcode;
	}

	uint16_t CPU::Random() const
	{
		return dist(engine);
	}

	void CPU::OP_Misc(uint16_t opcode)
	{
	}

	void CPU::OP_Arith(uint16_t opcode)
	{
	}

	void CPU::OP_Key(uint16_t opcode)
	{
	}

	void CPU::OP_Special(uint16_t opcode)
	{
	}

	void CPU::OP_0nnn(uint16_t opcode)
	{
	}

	void CPU::OP_00e0(uint16_t opcode)
	{
		display.Clear();
	}

	void CPU::OP_00ee(uint16_t opcode)
	{
		PC = stack[SP--];
	}

	void CPU::OP_1nnn(uint16_t opcode)
	{
		PC = LastThreeNibbles(opcode);
	}

	void CPU::OP_2nnn(uint16_t opcode)
	{
		stack[++SP] = PC;

		PC = LastThreeNibbles(opcode);
	}

	void CPU::OP_3xnn(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t nn = LastTwoNibbles(opcode);

		if (V[x] == nn)
		{
			PC += 2;
		}
	}

	void CPU::OP_4xnn(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t nn = LastTwoNibbles(opcode);

		if (V[x] != nn)
		{
			PC += 2;
		}
	}

	void CPU::OP_5xy0(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t y = GetYNibble(opcode);

		if (V[x] == V[y])
		{
			PC += 2;
		}
	}

	void CPU::OP_6xnn(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t nn = LastTwoNibbles(opcode);

		V[x] = nn;
	}

	void CPU::OP_7xnn(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t nn = LastTwoNibbles(opcode);

		V[x] += nn;
	}

	void CPU::OP_8xy0(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t y = GetYNibble(opcode);

		V[x] = V[y];
	}

	void CPU::OP_8xy1(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t y = GetYNibble(opcode);

		V[x] |= V[y];
	}

	void CPU::OP_8xy2(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t y = GetYNibble(opcode);

		V[x] &= V[y];
	}

	void CPU::OP_8xy3(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t y = GetYNibble(opcode);

		V[x] ^= V[y];
	}

	void CPU::OP_8xy4(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t y = GetYNibble(opcode);
		const uint16_t sum = static_cast<uint16_t>(V[x]) + V[y];

		V[x] = sum & 0xFF;

		// Set carry
		V[0xF] = sum > 0xFF;
	}

	void CPU::OP_8xy5(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t y = GetYNibble(opcode);

		// Set !borrow
		V[0xF] = V[x] >= V[y];

		V[x] -= V[y];
	}

	void CPU::OP_8xy6(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);

		V[0xF] = V[x] & 0x1;

		V[x] >>= 1;
	}

	void CPU::OP_8xy7(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t y = GetYNibble(opcode);

		// Set !borrow
		V[0xF] = V[y] >= V[x];

		V[x] = V[y] - V[x];
	}

	void CPU::OP_8xye(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);

		V[0xF] = (V[x] & 0x80) != 0;

		V[x] <<= 1;
	}

	void CPU::OP_9xy0(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t y = GetYNibble(opcode);

		if (V[x] != V[y])
		{
			PC += 2;
		}
	}

	void CPU::OP_annn(uint16_t opcode)
	{
		I = LastThreeNibbles(opcode);
	}

	void CPU::OP_bnnn(uint16_t opcode)
	{
		PC = LastThreeNibbles(opcode) + V[0];
	}

	void CPU::OP_cxnn(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t nn = LastTwoNibbles(opcode);

		V[x] = Random() & nn;
	}

	void CPU::OP_dxyn(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t y = GetYNibble(opcode);
		const uint8_t n = LastNibble(opcode);

		const uint8_t Vx = V[x];
		const uint8_t Vy = V[y];

		V[0xF] = 0;

		for (uint8_t line = 0; line < n; line++)
		{
			const uint8_t sprite = memory[I + line];
			for (uint8_t col = 0; col < 8; col++)
			{
				// Pixel position on screen
				const uint8_t Px = Vx + col;
				const uint8_t Py = Vy + line;

				const uint8_t bit = (sprite >> (7 - col)) && true;
				const uint8_t pixel = display.GetPixel(Px, Py);
				const uint8_t result = pixel ^ bit;

				V[0xF] |= pixel & bit;
				display.SetPixel(Px, Py, result);
			}
		}
	}

	void CPU::OP_ex9e(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);

		if (keyboard.IsKeyPressed(V[x] & 0xF))
		{
			PC += 2;
		}
	}

	void CPU::OP_exa1(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);

		if (!keyboard.IsKeyPressed(V[x] & 0xF))
		{
			PC += 2;
		}
	}

	void CPU::OP_fx07(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);

		V[x] = delayTimer;
	}

	void CPU::OP_fx0a(uint16_t opcode)
	{
	}

	void CPU::OP_fx15(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);

		delayTimer = V[x];
	}

	void CPU::OP_fx18(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);

		soundTimer = V[x];
	}

	void CPU::OP_fx1e(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);

		I += V[x];
	}

	void CPU::OP_fx29(uint16_t opcode)
	{
	}

	void CPU::OP_fx33(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);
		const uint8_t Vx = V[x];
		const uint8_t hundreds = Vx / 100;
		const uint8_t tens = (Vx / 10) % 10;
		const uint8_t ones = Vx % 10;

		memory[I] = hundreds;
		memory[I + 1] = tens;
		memory[I + 2] = ones;
	}

	void CPU::OP_fx55(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);

		for (uint8_t reg = 0; reg <= x; reg++)
		{
			memory[I + reg] = V[reg];
		}
	}

	void CPU::OP_fx65(uint16_t opcode)
	{
		const uint8_t x = GetXNibble(opcode);

		for (uint8_t reg = 0; reg <= x; reg++)
		{
			V[reg] = memory[I + reg];
		}
	}
}
