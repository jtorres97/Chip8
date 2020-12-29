#include "CPU.h"
#include "Memory.h"

namespace chip8
{
	CPU::CPU(Memory& memory): memory(memory), I(0), PC(0), delayTimer(0), soundTimer(0), SP(0)
	{
	}

	void CPU::Execute()
	{
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
		PC = chip8::Memory::ProgramStart();
		SP = 0;
		delayTimer = 0;
		soundTimer = 0;
	}


	void CPU::OP_0nnn(uint16_t opcode)
	{
	}

	void CPU::OP_00e0(uint16_t opcode)
	{
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
	}

	void CPU::OP_bnnn(uint16_t opcode)
	{
	}

	void CPU::OP_cxnn(uint16_t opcode)
	{
	}

	void CPU::OP_dxyn(uint16_t opcode)
	{
	}

	void CPU::OP_ex9e(uint16_t opcode)
	{
	}

	void CPU::OP_exa1(uint16_t opcode)
	{
	}

	void CPU::OP_fx07(uint16_t opcode)
	{
	}

	void CPU::OP_fx0a(uint16_t opcode)
	{
	}

	void CPU::OP_fx15(uint16_t opcode)
	{
	}

	void CPU::OP_fx18(uint16_t opcode)
	{
	}

	void CPU::OP_fx1e(uint16_t opcode)
	{
	}

	void CPU::OP_fx29(uint16_t opcode)
	{
	}

	void CPU::OP_fx33(uint16_t opcode)
	{
	}

	void CPU::OP_fx55(uint16_t opcode)
	{
	}

	void CPU::OP_fx65(uint16_t opcode)
	{
	}
}
