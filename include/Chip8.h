#pragma once

#include <string>

#include "CPU.h"
#include "Memory.h"
#include "Display.h"
#include "Keyboard.h"

namespace chip8
{
    class Chip8 
    {
    public:
        Chip8();

        bool LoadRom(const std::string& file);
        void Run();

    private:
        Memory memory;
        Display display;
        Keyboard keyboard;
        CPU cpu;
    };
}
