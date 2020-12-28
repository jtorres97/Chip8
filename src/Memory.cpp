#include "Memory.h"

namespace chip8
{
	bool Memory::LoadRom(const std::vector<uint8_t>& rom)
	{
		const auto romStart = std::begin(m_memory) + ProgramStart();
		std::copy(std::begin(rom), std::end(rom), romStart);
		return true;
	}
}
