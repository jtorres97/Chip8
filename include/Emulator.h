#pragma once

#include <string>

#include "Memory.h"

namespace chip8
{
    class Emulator 
    {
    public:
        Emulator();

        bool LoadRom(const std::string& file);
        void Run();

    private:
        Memory m_memory;
    };
}
