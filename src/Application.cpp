#include "Application.h"

#include <stdexcept>
#include <SDL2/SDL.h>

Application::Application()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		throw std::runtime_error("Failed to initialize SDL!");
	}
}

Application::~Application()
{
	SDL_Quit();
}
