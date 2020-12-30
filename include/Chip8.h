#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>

#include "Application.h"
#include "CPU.h"
#include "Memory.h"
#include "Display.h"
#include "Keyboard.h"

namespace chip8
{
    class Chip8 : public Application
    {
        using SDL_WindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
        using SDL_RendererPtr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
        using SDL_TexturePtr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
        using SDL_PixelFormatPtr = std::unique_ptr<SDL_PixelFormat, decltype(&SDL_FreeFormat)>;
    public:
        Chip8();

        bool LoadRom(const std::string& file);
        void Run();

    private:
        void Render();
        void UpdateTexture();
        void HandleInput(const SDL_KeyboardEvent& event);
    	
        Memory memory;
        Display display;
        Keyboard keyboard;
        CPU cpu;

        SDL_WindowPtr window = SDL_WindowPtr(nullptr, SDL_DestroyWindow);
        SDL_RendererPtr renderer = SDL_RendererPtr(nullptr, SDL_DestroyRenderer);
        SDL_TexturePtr texture = SDL_TexturePtr(nullptr, SDL_DestroyTexture);
        SDL_PixelFormatPtr format = SDL_PixelFormatPtr(nullptr, SDL_FreeFormat);

        const size_t scale;
        const size_t width;
        const size_t height;

        const size_t instructionsPerSecond;
        const size_t timersFrequency;
        const size_t instructionsPerTimerUpdate;
    };
}
