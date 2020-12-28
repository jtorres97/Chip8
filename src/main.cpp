#include "Emulator.h"

#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Please specify a ROM file to load.\n";
		return 1;
	}

	chip8::Emulator emulator;

	if (!emulator.LoadRom(argv[1]))
	{
		std::cerr << "Failed to load ROM file.\n";
		return 1;
	}

	emulator.Run();
}