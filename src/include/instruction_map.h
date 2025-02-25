#include <memory>
#include <instruction_disam.h>

using instructionPointer = std::shared_ptr<instr> (*)(AddressMode, DisAsmState &);
#ifndef INSTRUCT_H
#define INSTRUCT_H
struct Instruction
{
    instructionPointer i;
    AddressMode addressmode;
};
#endif
void initializeInstructionMap();
Instruction GetInstruction(uint8_t opcode);
bool InstructionValid(uint8_t opcode);