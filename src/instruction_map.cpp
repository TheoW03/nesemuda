#include <memory>
#include <map>
#include <instruction_disam.h>

using instructionPointer = std::shared_ptr<instr> (*)(AddressMode, DisAsmState &);

struct Instruction
{
    instructionPointer i;
    AddressMode addressmode;
};

std::map<uint8_t, Instruction> instructionMap;

void initializeInstructionMap()
{
    instructionMap.insert(std::make_pair(0xA9, Instruction{(instructionPointer)LDA, AddressMode::IMMEDIATE}));
}
Instruction GetInstruction(uint8_t opcode)
{
    return instructionMap.at(opcode);
}
bool InstructionValid(uint8_t opcode)
{
    return instructionMap.find(opcode) != instructionMap.end();
}