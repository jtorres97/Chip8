#pragma once

#include <cstdint>
#include <array>

namespace chip8
{
	class Keyboard
	{
	public:
		void SetKeyPressed(uint8_t key, bool pressed);
		[[nodiscard]] bool IsKeyPressed(uint8_t key) const;
		[[nodiscard]] int GetKeyPressed() const;
		
	private:
		std::array<bool, 16> keys;
	};
}