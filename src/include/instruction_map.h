#include <memory>
#include <instruction_disam.h>

using instructionPointer = std::shared_ptr<instr> (*)(AddressMode, DisAsmState &, std::string);
#ifndef INSTRUCT_H
#define INSTRUCT_H
struct Instruction
{
    instructionPointer instructionFunction;
    AddressMode addressmode;
    std::string name;
};
#endif
void initializeInstructionMap();
Instruction GetInstruction(uint8_t opcode);
bool InstructionValid(uint8_t opcode);