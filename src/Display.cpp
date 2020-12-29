#include "Display.h"

namespace chip8
{
	Display::Display() : display(GetSizeX() * GetSizeY())
	{
	}

	void Display::SetPixel(uint8_t col, uint8_t row, uint8_t value)
	{
		Wrap(col, row);

		display[GetSizeX() * row + col] = value;
	}

	uint8_t Display::GetPixel(uint8_t col, uint8_t row) const
	{
		Wrap(col, row);

		return display[GetSizeX() * row + col];
	}

	void Display::Clear()
	{
		std::fill(display.begin(), display.end(), 0);
	}
}
