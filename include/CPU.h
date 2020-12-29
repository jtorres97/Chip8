#pragma once

#include <cstdint>
#include <array>

namespace chip8
{
	class Memory;

	class CPU
	{
	public:
		CPU(Memory& memory);

		void Execute();
		void UpdateTimers();
		void Reset();

	private:
		Memory& memory;
		std::array<uint16_t, 16> stack;

		std::array<uint8_t, 16> V; // General purpose registers
		uint16_t I; // I register
		uint16_t PC; // Program counter
		uint8_t delayTimer;
		uint8_t soundTimer;
		uint8_t SP; // Stack pointer
	};
}