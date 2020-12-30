#include "Chip8.h"

#include <cstdint>
#include <fstream>
#include <vector>
#include <stdexcept>

namespace chip8
{
	Chip8::Chip8(): cpu(memory, display, keyboard), scale(10), width(Display::GetSizeX()), height(Display::GetSizeY())
	{
		window = SDL_WindowPtr(SDL_CreateWindow("Chip8 Emulator (WIP)",
		                                        SDL_WINDOWPOS_CENTERED,
		                                        SDL_WINDOWPOS_CENTERED,
		                                        width * scale,
		                                        height * scale,
		                                        SDL_WINDOW_SHOWN), SDL_DestroyWindow);

		if (!window)
		{
			throw std::runtime_error("Failed to create SDL window");
		}

		renderer = SDL_RendererPtr(SDL_CreateRenderer(window.get(), -1,
		                                              SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);

		if (!renderer)
		{
			throw std::runtime_error("Failed to create SDL renderer");
		}

		SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
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
		bool quit = false;
		SDL_Event event;

		while (!quit)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			cpu.Execute();
			cpu.UpdateTimers();

			Render();

			SDL_Delay(1);
		}
	}

	void Chip8::Render()
	{
		SDL_RenderClear(renderer.get());
		SDL_RenderPresent(renderer.get());
	}
}
