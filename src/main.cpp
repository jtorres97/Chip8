#include "Chip8.h"

#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Please specify a ROM file to load.\n";
		return 1;
	}

	try
	{
		chip8::Chip8 emulator;

		if (!emulator.LoadRom(argv[1]))
		{
			std::cerr << "Failed to load ROM file.\n";
			return 1;
		}

		emulator.Run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
