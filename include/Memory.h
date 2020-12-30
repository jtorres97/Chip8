#pragma once

#include <cstdint>
#include <vector>
#include <array>

namespace chip8
{
	class Memory
	{
	public:
		Memory();

		static constexpr uint16_t ProgramStart() { return 0x200; }
		static constexpr uint16_t FontStart() { return 0x50; }

		bool LoadRom(const std::vector<uint8_t>& rom);

		uint8_t& operator[](uint16_t address)
		{
			return memory[address & 0xFFF];
		}
		
	private:
		void LoadFont();
		
		std::array<uint8_t, 4 * 1024> memory;
	};
}