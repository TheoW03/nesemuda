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
    instructionMap.insert(std::make_pair(0xA5, Instruction{(instructionPointer)LDA, AddressMode::ZERO_PAGE}));
    instructionMap.insert(std::make_pair(0xB5, Instruction{(instructionPointer)LDA, AddressMode::ZERO_PAGE_X}));
    instructionMap.insert(std::make_pair(0xAD, Instruction{(instructionPointer)LDA, AddressMode::ABSOLUTE}));
    instructionMap.insert(std::make_pair(0xBD, Instruction{(instructionPointer)LDA, AddressMode::ABSOLUTE_X}));
    instructionMap.insert(std::make_pair(0xB9, Instruction{(instructionPointer)LDA, AddressMode::ABSOLUTE_Y}));
    instructionMap.insert(std::make_pair(0xA1, Instruction{(instructionPointer)LDA, AddressMode::INDIRECT_X}));
    instructionMap.insert(std::make_pair(0xB1, Instruction{(instructionPointer)LDA, AddressMode::INDIRECT_Y}));
    instructionMap.insert(std::make_pair(0x4C, Instruction{(instructionPointer)JMP, AddressMode::ABSOLUTE}));
    instructionMap.insert(std::make_pair(0x40, Instruction{(instructionPointer)RTI, AddressMode::ABSOLUTE}));

    instructionMap.insert(std::make_pair(0xF0, Instruction{(instructionPointer)BEQ, AddressMode::RELATIVE}));
    instructionMap.insert(std::make_pair(0xD0, Instruction{(instructionPointer)BNE, AddressMode::RELATIVE}));
}
Instruction GetInstruction(uint8_t opcode)
{
    return instructionMap.at(opcode);
}
bool InstructionValid(uint8_t opcode)
{
    return instructionMap.find(opcode) != instructionMap.end();
}