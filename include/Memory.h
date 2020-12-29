#pragma once

#include <cstdint>
#include <vector>
#include <array>

namespace chip8
{
	class Memory
	{
	public:
		Memory() = default;

		// Program start address
		static constexpr uint16_t ProgramStart() { return 0x200; }

		bool LoadRom(const std::vector<uint8_t>& rom);
		
	private:
		std::array<uint8_t, 4 * 1024> memory;
	};
}