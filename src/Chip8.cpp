#include "Chip8.h"

#include <cstdint>
#include <fstream>
#include <vector>
#include <stdexcept>

namespace chip8
{
	Chip8::Chip8(): cpu(memory, display, keyboard), scale(10), width(Display::GetSizeX()), height(Display::GetSizeY()),
	                instructionsPerSecond(840),
	                timersFrequency(60),
	                instructionsPerTimerUpdate(instructionsPerSecond / timersFrequency)
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

		texture = SDL_TexturePtr(SDL_CreateTexture(renderer.get(),
		                                           SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height),
		                         SDL_DestroyTexture);

		if (!texture)
		{
			throw std::runtime_error("Failed to create SDL texture");
		}

		format = SDL_PixelFormatPtr(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), SDL_FreeFormat);

		if (!format)
		{
			throw std::runtime_error("Failed to create SDL pixel format");
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
		cpu.Reset();

		const size_t dt = 1000 / timersFrequency;
		bool quit = false;
		SDL_Event event;

		while (!quit)
		{
			const uint32_t ticks = SDL_GetTicks();
			
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = true;
					}
					break;
				case SDL_KEYUP:
					HandleInput(event.key);
					break;
				}
			}

			cpu.UpdateTimers();

			for (size_t i = 0; i < instructionsPerTimerUpdate; i++)
			{
				cpu.Execute();
			}

			Render();

			const uint32_t delta = SDL_GetTicks() - ticks;
			if (delta < dt)
			{
				SDL_Delay(dt - delta);
			}
		}
	}

	void Chip8::Render()
	{
		UpdateTexture();

		SDL_Renderer* r = renderer.get();
		SDL_RenderClear(r);
		SDL_RenderCopy(r, texture.get(), nullptr, nullptr);
		SDL_RenderPresent(r);
	}

	void Chip8::UpdateTexture()
	{
		uint32_t* pixels;
		int pitch = 0;

		SDL_LockTexture(texture.get(), nullptr, reinterpret_cast<void**>(&pixels), &pitch);

		for (size_t y = 0; y < height; y++)
		{
			for (size_t x = 0; x < width; x++)
			{
				const uint8_t color = display.GetPixel(x, y) ? 255 : 0;

				pixels[width * y + x] = SDL_MapRGB(format.get(), color, color, color);
			}
		}

		SDL_UnlockTexture(texture.get());
	}

	void Chip8::HandleInput(const SDL_KeyboardEvent& event)
	{
		// Map SDL keys to Chip8 keys
		static const SDL_Keycode keys[16] = {
			SDLK_x, // 0
			SDLK_1, // 1
			SDLK_2, // 2
			SDLK_3, // 3
			SDLK_q, // 4
			SDLK_w, // 5
			SDLK_e, // 6
			SDLK_a, // 7
			SDLK_s, // 8
			SDLK_d, // 9
			SDLK_z, // A
			SDLK_c, // B
			SDLK_4, // C
			SDLK_r, // D
			SDLK_f, // E
			SDLK_v // F
		};

		const bool pressed = event.type == SDL_KEYDOWN;
		const SDL_Keycode code = event.keysym.sym;

		for (size_t i = 0; i < 16; i++)
		{
			if (code == keys[i])
			{
				keyboard.SetKeyPressed(i, pressed);
				break;
			}
		}
	}
}
