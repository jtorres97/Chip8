#pragma once

#include <string>

namespace chip8
{
    class Emulator 
    {
    public:
        Emulator();

        bool LoadRom(const std::string& file);
        void Run();
    };
}
