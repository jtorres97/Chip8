#include "Keyboard.h"

namespace chip8
{
	void Keyboard::SetKeyPressed(uint8_t key, bool pressed)
	{
		keys[key & 0xF] = pressed;
	}

	bool Keyboard::IsKeyPressed(uint8_t key) const
	{
		return keys[key & 0xF];
	}

	int Keyboard::GetKeyPressed() const
	{
		for (size_t i = 0; i < keys.size(); i++)
		{
			if (IsKeyPressed(i))
			{
				return i;
			}
		}

		return -1;
	}
}
