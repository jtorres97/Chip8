#pragma once

#include <string>

#include "CPU.h"
#include "Memory.h"
#include "Display.h"

namespace chip8
{
    class Emulator 
    {
    public:
        Emulator();

        bool LoadRom(const std::string& file);
        void Run();

    private:
        Memory memory;
        Display display;
        CPU cpu;
    };
}
