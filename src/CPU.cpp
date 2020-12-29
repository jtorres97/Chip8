#include "CPU.h"
#include "Memory.h"

namespace chip8
{
	CPU::CPU(Memory& memory): memory(memory), I(0), PC(0), delayTimer(0), soundTimer(0), SP(0)
	{
	}

	void CPU::Execute()
	{
	}

	void CPU::UpdateTimers()
	{
		if (delayTimer)
		{
			delayTimer--;
		}
		if (soundTimer)
		{
			soundTimer--;
		}
	}

	void CPU::Reset()
	{
		stack.fill(0);
		V.fill(0);
		I = 0;
		PC = chip8::Memory::ProgramStart();
		SP = 0;
		delayTimer = 0;
		soundTimer = 0;
	}
}
