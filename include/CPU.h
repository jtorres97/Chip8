#pragma once

#include <cstdint>
#include <array>
#include <random>
#include <unordered_map>

namespace chip8
{
	class Memory;
	class Display;
	class Keyboard;

	class CPU
	{
		using InstructionHandler = void(CPU::*)(uint16_t);
	public:
		CPU(Memory& memory, Display& display, Keyboard& keyboard);

		void Execute();
		void UpdateTimers();
		void Reset();

	private:
		[[nodiscard]] uint16_t Random() const;

		/*
		 * Instruction handlers
		 */
		void OP_Misc(uint16_t opcode);
		void OP_Arith(uint16_t opcode);
		void OP_Key(uint16_t opcode);
		void OP_Special(uint16_t opcode);
		
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
		void OP_annn(uint16_t opcode); // Set I = nnn
		void OP_bnnn(uint16_t opcode); // Jump to nnn + v0
		void OP_cxnn(uint16_t opcode); // Set Vx = Random() & nn
		void OP_dxyn(uint16_t opcode); // Display n-byte sprite starting at memory location I
		void OP_ex9e(uint16_t opcode); // Skip next instruction if key with the value of Vx is pressed
		void OP_exa1(uint16_t opcode); // Skip next instruction if key with the value of Vx is not pressed
		void OP_fx07(uint16_t opcode); // Set Vx = dt
		void OP_fx0a(uint16_t opcode); // Wait for a key press, store the value of the key in Vx
		void OP_fx15(uint16_t opcode); // Set dt = Vx
		void OP_fx18(uint16_t opcode); // Set st = Vx
		void OP_fx1e(uint16_t opcode); // Set I = I + Vx
		void OP_fx29(uint16_t opcode); // Set I = memory location of sprite for digit Vx
		void OP_fx33(uint16_t opcode); // Store BCD representation of Vx in memory		
		void OP_fx55(uint16_t opcode); // Store registers V0 through Vx in memory starting at I
		void OP_fx65(uint16_t opcode); // Read registers V0 through Vx from memory starting at I

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
		Keyboard& keyboard;

		std::array<InstructionHandler, 16> instructions;
		std::array<InstructionHandler, 9> arithmetic; // Arithmetic instructions 8xy0 - 8xye
		std::unordered_map<uint8_t, InstructionHandler> special; // Special instructions fx07 - fx65

		std::array<uint16_t, 16> stack;

		std::array<uint8_t, 16> V; // General purpose registers
		uint16_t I; // I register
		uint16_t PC; // Program counter
		uint8_t delayTimer;
		uint8_t soundTimer;
		uint8_t SP; // Stack pointer

		mutable std::mt19937 engine;
		mutable std::uniform_int_distribution<uint16_t> dist;
	};
}