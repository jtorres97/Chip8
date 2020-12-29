#include "Chip8.h"

#include <cstdint>
#include <fstream>
#include <vector>

namespace chip8
{
	Chip8::Chip8(): cpu(memory, display, keyboard)
	{
	}

	bool Chip8::LoadRom(const std::string& file)
	{
		std::ifstream inFile(file, std::ios_base::binary);
		if (!inFile)
		{
			return false;
		}

		inFile.seekg(0, std::ifstream::end);
		const size_t length = inFile.tellg();
		inFile.seekg(0, std::ifstream::beg);
		std::vector<uint8_t> rom(length);
		inFile.read(reinterpret_cast<char*>(&rom[0]), length);

		return memory.LoadRom(rom);
	}

	void Chip8::Run()
	{
		cpu.Execute();
		cpu.UpdateTimers();
	}
}
