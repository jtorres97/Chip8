#pragma once

#include <cstdint>
#include <vector>

namespace chip8
{
	class Display
	{
	public:
		Display();

		static constexpr size_t GetSizeX() { return 64; }
		static constexpr size_t GetSizeY() { return 32; }

		void SetPixel(uint8_t col, uint8_t row, uint8_t value);
		[[nodiscard]] uint8_t GetPixel(uint8_t col, uint8_t row) const;

		void Clear();
		
	private:
		void Wrap(uint8_t& col, uint8_t& row) const
		{
			col %= GetSizeX();
			row %= GetSizeY();
		}

		std::vector<uint8_t> display;
	};
}