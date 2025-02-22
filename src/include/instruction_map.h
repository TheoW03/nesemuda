#include <memory>
#include <instruction_disam.h>

using instructionPointer = std::shared_ptr<instr> (*)(AddressMode, DisAsmState &);

struct Instruction
{
    instructionPointer i;
    AddressMode addressmode;
};
void initializeInstructionMap();
Instruction GetInstruction(uint8_t opcode);
bool InstructionValid(uint8_t opcode);