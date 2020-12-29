#pragma once

#include <cstdint>
#include <array>

namespace chip8
{
	class Memory;
	class Display;

	class CPU
	{
	public:
		CPU(Memory& memory, Display& display);

		void Execute();
		void UpdateTimers();
		void Reset();

	private:
		void OP_0nnn(uint16_t opcode); // Jump to machine code routine at nnn
		void OP_00e0(uint16_t opcode); // Clear the display
		void OP_00ee(uint16_t opcode); // Return from a subroutine
		void OP_1nnn(uint16_t opcode); // Jump to location nnn
		void OP_2nnn(uint16_t opcode); // Call subroutine at nnn
		void OP_3xnn(uint16_t opcode); // Skip next instruction if Vx == nn
		void OP_4xnn(uint16_t opcode); // Skip next instruction if Vx != nn
		void OP_5xy0(uint16_t opcode); // Skip next instruction if Vx == Vy
		void OP_6xnn(uint16_t opcode); // Set Vx = nn
		void OP_7xnn(uint16_t opcode); // Set Vx = Vx + nn
		void OP_8xy0(uint16_t opcode); // Set Vx = Vy
		void OP_8xy1(uint16_t opcode); // Set Vx = Vx | Vy
		void OP_8xy2(uint16_t opcode); // Set Vx = Vx & Vy
		void OP_8xy3(uint16_t opcode); // Set Vx = Vx ^ Vy
		void OP_8xy4(uint16_t opcode); // Set Vx = Vx + Vy, Set Vf = carry
		void OP_8xy5(uint16_t opcode); // Set Vx = Vx - Vy, Set Vf = !borrow
		void OP_8xy6(uint16_t opcode); // Set Vx = Vx >> 1
		void OP_8xy7(uint16_t opcode); // Set Vx = Vy - Vx, Set vf = !borrow
		void OP_8xye(uint16_t opcode); // Set Vx = Vx << 1
		void OP_9xy0(uint16_t opcode); // Skip next instruction if Vx != Vy
		void OP_annn(uint16_t opcode); // Set i = nnn
		void OP_bnnn(uint16_t opcode); // Jump to nnn + v0
		void OP_cxnn(uint16_t opcode); // Set Vx = rand() & nn
		void OP_dxyn(uint16_t opcode); // Display n-byte sprite starting at memory location i
		void OP_ex9e(uint16_t opcode); // Skip next instruction if key with the value of Vx is pressed
		void OP_exa1(uint16_t opcode); // Skip next instruction if key with the value of Vx is not pressed
		void OP_fx07(uint16_t opcode); // Set Vx = dt
		void OP_fx0a(uint16_t opcode); // Wait for a key press, store the value of the key in Vx
		void OP_fx15(uint16_t opcode); // Set dt = Vx
		void OP_fx18(uint16_t opcode); // Set st = Vx
		void OP_fx1e(uint16_t opcode); // Set i = i + Vx
		void OP_fx29(uint16_t opcode); // Set i = memory location of sprite for digit Vx
		void OP_fx33(uint16_t opcode); // Store BCD representation of Vx in memory		
		void OP_fx55(uint16_t opcode); // Store registers V0 through Vx in memory starting at i
		void OP_fx65(uint16_t opcode); // Read registers V0 through Vx from memory starting at i

		[[nodiscard]] static uint16_t LastThreeNibbles(uint16_t opcode)
		{
			return opcode & 0xFFF;
		}

		[[nodiscard]] static uint8_t LastTwoNibbles(uint16_t opcode)
		{
			return opcode & 0xFF;
		}

		[[nodiscard]] static uint8_t LastNibble(uint16_t opcode)
		{
			return opcode & 0xF;
		}

		[[nodiscard]] static uint8_t GetXNibble(uint16_t opcode)
		{
			return (opcode >> 8) & 0xF;
		}

		[[nodiscard]] static uint8_t GetYNibble(uint16_t opcode)
		{
			return (opcode >> 4) & 0xF;
		}
		
		Memory& memory;
		Display& display;
		std::array<uint16_t, 16> stack;

		std::array<uint8_t, 16> V; // General purpose registers
		uint16_t I; // I register
		uint16_t PC; // Program counter
		uint8_t delayTimer;
		uint8_t soundTimer;
		uint8_t SP; // Stack pointer
	};
}