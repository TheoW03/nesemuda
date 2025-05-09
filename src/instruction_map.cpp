#include <memory>
#include <map>
#include <instruction_disam.h>

// using instructionPointer = std::shared_ptr<instr> (*)(AddressMode, DisAsmState &);
using InstructionProcedure = std::shared_ptr<instr> (*)(AddressMode, DisAsmState &, std::string);

struct Instruction
{
    InstructionProcedure i;
    AddressMode addressmode;
    std::string name;
};

std::map<uint8_t, Instruction> instructionMap;

void initializeInstructionMap()
{
    using std::make_pair;
#pragma region LDA

    instructionMap.insert(make_pair(0xA9, Instruction{
                                              (InstructionProcedure)disassemble_MultiByteInstr,
                                              AddressMode::IMMEDIATE,
                                              "lda"}));
    instructionMap.insert(make_pair(0xA5, Instruction{
                                              (InstructionProcedure)disassemble_MultiByteInstr,
                                              AddressMode::ZERO_PAGE,
                                              "lda"}));

    instructionMap.insert(make_pair(0xB5, Instruction{
                                              (InstructionProcedure)disassemble_MultiByteInstr,
                                              AddressMode::ZERO_PAGE_X,
                                              "lda"}));

    instructionMap.insert(make_pair(0xAD, Instruction{
                                              (InstructionProcedure)disassemble_MultiByteInstr,
                                              AddressMode::ABSOLUTE,
                                              "lda"}));

    instructionMap.insert(make_pair(0xBD, Instruction{
                                              (InstructionProcedure)disassemble_MultiByteInstr,
                                              AddressMode::ABSOLUTE_X,
                                              "lda"}));
    instructionMap.insert(make_pair(0xB9, Instruction{
                                              (InstructionProcedure)disassemble_MultiByteInstr,
                                              AddressMode::ABSOLUTE_Y,
                                              "lda"}));
    instructionMap.insert(make_pair(0xA1, Instruction{
                                              (InstructionProcedure)disassemble_MultiByteInstr,
                                              AddressMode::INDIRECT_X,
                                              "lda"}));
    instructionMap.insert(make_pair(0xB1, Instruction{
                                              (InstructionProcedure)disassemble_MultiByteInstr,
                                              AddressMode::INDIRECT_Y,
                                              "lda"}));
#pragma endregion
#pragma region LDX

    instructionMap.insert(make_pair(0xA2, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::IMMEDIATE, "ldx"}));
    instructionMap.insert(make_pair(0xA6, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "ldx"}));
    instructionMap.insert(make_pair(0xB6, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE_Y, "ldx"}));
    instructionMap.insert(make_pair(0xAE, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "ldx"}));
    instructionMap.insert(make_pair(0xBE, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE_Y, "ldx"}));
#pragma endregion

#pragma region LDY

    instructionMap.insert(make_pair(0xA0, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::IMMEDIATE, "ldy"}));
    instructionMap.insert(make_pair(0xA4, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "ldy"}));
    instructionMap.insert(make_pair(0xB4, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE_X, "ldy"}));
    instructionMap.insert(make_pair(0xAC, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "ldy"}));
    instructionMap.insert(make_pair(0xBC, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE_X, "ldy"}));
#pragma endregion
    instructionMap.insert(std::make_pair(0x4C, Instruction{(InstructionProcedure)JMP, AddressMode::ABSOLUTE, ""}));
    instructionMap.insert(make_pair(0x20, Instruction{(InstructionProcedure)JSR, AddressMode::ABSOLUTE, ""}));

    instructionMap.insert(make_pair(0xF0, Instruction{(InstructionProcedure)disassemble_Branch, AddressMode::RELATIVE, "beq"}));
    instructionMap.insert(make_pair(0xD0, Instruction{(InstructionProcedure)disassemble_Branch, AddressMode::RELATIVE, "bne"}));

    instructionMap.insert(make_pair(0x90, Instruction{(InstructionProcedure)disassemble_Branch, AddressMode::RELATIVE, "bcc"}));

    instructionMap.insert(make_pair(0xB0, Instruction{(InstructionProcedure)disassemble_Branch, AddressMode::RELATIVE, "bcs"}));

    instructionMap.insert(make_pair(0x10, Instruction{(InstructionProcedure)disassemble_Branch, AddressMode::RELATIVE, "bpl"}));

    instructionMap.insert(make_pair(0x30, Instruction{(InstructionProcedure)disassemble_Branch, AddressMode::RELATIVE, "bmi"}));

    instructionMap.insert(make_pair(0x50, Instruction{(InstructionProcedure)disassemble_Branch, AddressMode::RELATIVE, "bvc"}));

    instructionMap.insert(make_pair(0x70, Instruction{(InstructionProcedure)disassemble_Branch, AddressMode::RELATIVE, "bvs"}));
    instructionMap.insert(make_pair(0x40, Instruction{(InstructionProcedure)disassemble_RtsRti, AddressMode::IMPLIED, "rti"}));
    instructionMap.insert(make_pair(0x60, Instruction{(InstructionProcedure)disassemble_RtsRti, AddressMode::IMPLIED, "rts"}));

    //     instructionMap.insert(make_pair(0xA5, Instruction{(instructionPointer)LDA, AddressMode::ZERO_PAGE}));
    //     instructionMap.insert(make_pair(0xB5, Instruction{(instructionPointer)LDA, AddressMode::ZERO_PAGE_X}));
    // instructionMap.insert(make_pair(0xAD, Instruction{(instructionPointer)LDA, AddressMode::ABSOLUTE}));
    //     instructionMap.insert(make_pair(0xBD, Instruction{(instructionPointer)LDA, AddressMode::ABSOLUTE_X}));
    //     instructionMap.insert(make_pair(0xB9, Instruction{(instructionPointer)LDA, AddressMode::ABSOLUTE_Y}));
    //     instructionMap.insert(make_pair(0xA1, Instruction{(instructionPointer)LDA, AddressMode::INDIRECT_X}));
    //     instructionMap.insert(make_pair(0xB1, Instruction{(instructionPointer)LDA, AddressMode::INDIRECT_Y}));
    // #pragma endregion
    instructionMap.insert(make_pair(0x18, Instruction{(InstructionProcedure)disassemble_Onebyte, AddressMode::IMPLIED, "clc"})); //"implied"

    instructionMap.insert(make_pair(0x38, Instruction{(InstructionProcedure)disassemble_Onebyte, AddressMode::IMPLIED, "sec"}));

    instructionMap.insert(make_pair(0xD8, Instruction{(InstructionProcedure)disassemble_Onebyte, AddressMode::IMPLIED, "cld"}));

    instructionMap.insert(make_pair(0xF8, Instruction{(InstructionProcedure)disassemble_Onebyte, AddressMode::IMPLIED, "sed"}));

    instructionMap.insert(make_pair(0x78, Instruction{(InstructionProcedure)disassemble_Onebyte, AddressMode::IMPLIED, "sei"}));

    instructionMap.insert(make_pair(0x58, Instruction{(InstructionProcedure)disassemble_Onebyte, AddressMode::IMPLIED, "cli"}));

    instructionMap.insert(make_pair(0xB8, Instruction{(InstructionProcedure)disassemble_Onebyte, AddressMode::IMPLIED, "clv"}));

    // instructionMap.insert(make_pair(0x40, Instruction{(instructionPointer)RTI, AddressMode::IMPLIED}));
    // #pragma region LDX

    //     instructionMap.insert(make_pair(0xA2, Instruction{(instructionPointer)LDX, AddressMode::IMMEDIATE}));
    //     instructionMap.insert(make_pair(0xA6, Instruction{(instructionPointer)LDX, AddressMode::ZERO_PAGE}));
    //     instructionMap.insert(make_pair(0xB6, Instruction{(instructionPointer)LDX, AddressMode::ZERO_PAGE_Y}));
    //     instructionMap.insert(make_pair(0xAE, Instruction{(instructionPointer)LDX, AddressMode::ABSOLUTE}));
    //     instructionMap.insert(make_pair(0xBE, Instruction{(instructionPointer)LDX, AddressMode::ABSOLUTE_Y}));

    // #pragma endregion

    // #pragma region LDY

    //     instructionMap.insert(make_pair(0xA0, Instruction{(instructionPointer)LDY, AddressMode::IMMEDIATE}));
    //     instructionMap.insert(make_pair(0xA4, Instruction{(instructionPointer)LDY, AddressMode::ZERO_PAGE}));
    //     instructionMap.insert(make_pair(0xB4, Instruction{(instructionPointer)LDY, AddressMode::ZERO_PAGE_X}));
    //     instructionMap.insert(make_pair(0xAC, Instruction{(instructionPointer)LDY, AddressMode::ABSOLUTE}));
    //     instructionMap.insert(make_pair(0xBC, Instruction{(instructionPointer)LDY, AddressMode::ABSOLUTE_X}));

    // #pragma endregion

#pragma region ADC

    instructionMap.insert(make_pair(0x69, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::IMMEDIATE, "adc"}));
    instructionMap.insert(make_pair(0x65, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "adc"}));
    instructionMap.insert(make_pair(0x75, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE_X, "adc"}));
    instructionMap.insert(make_pair(0x6D, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "adc"}));
    instructionMap.insert(make_pair(0x7D, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE_X, "adc"}));
    instructionMap.insert(make_pair(0x79, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE_Y, "adc"}));
    instructionMap.insert(make_pair(0x71, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::INDIRECT_X, "adc"}));
    instructionMap.insert(make_pair(0x61, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::INDIRECT_Y, "adc"}));

#pragma endregion

#pragma region SBC

    instructionMap.insert(make_pair(0xE9, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::IMMEDIATE, "sbc"}));
    instructionMap.insert(make_pair(0xE5, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "sbc"}));
    instructionMap.insert(make_pair(0xF5, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE_X, "sbc"}));
    instructionMap.insert(make_pair(0xED, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "sbc"}));
    instructionMap.insert(make_pair(0xFD, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE_X, "sbc"}));
    instructionMap.insert(make_pair(0xF9, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE_Y, "sbc"}));
    instructionMap.insert(make_pair(0xE1, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::INDIRECT_X, "sbc"}));
    instructionMap.insert(make_pair(0xF1, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::INDIRECT_Y, "sbc"}));

#pragma endregion
    instructionMap.insert(make_pair(0x85, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "sta"}));
    instructionMap.insert(make_pair(0x95, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE_X, "sta"}));
    instructionMap.insert(make_pair(0x8D, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "sta"}));
    instructionMap.insert(make_pair(0x9D, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE_X, "sta"}));
    instructionMap.insert(make_pair(0x99, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE_Y, "sta"}));
    instructionMap.insert(make_pair(0x81, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::INDIRECT_X, "sta"}));
    instructionMap.insert(make_pair(0x91, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::INDIRECT_Y, "sta"}));

#pragma region STX
    instructionMap.insert(make_pair(0x86, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "stx"}));
    instructionMap.insert(make_pair(0x96, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE_X, "stx"}));
    instructionMap.insert(make_pair(0x8E, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "stx"}));

    instructionMap.insert(make_pair(0x84, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "sty"}));
    instructionMap.insert(make_pair(0x94, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE_X, "sty"}));
    instructionMap.insert(make_pair(0x8C, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "sty"}));

    instructionMap.insert(make_pair(0xE8, Instruction{(InstructionProcedure)disassemble_Onebyte, AddressMode::IMPLIED, "inx"}));
    instructionMap.insert(make_pair(0xC8, Instruction{(InstructionProcedure)disassemble_Onebyte, AddressMode::IMPLIED, "iny"}));

    instructionMap.insert(make_pair(0x9A, Instruction{(InstructionProcedure)disassemble_Onebyte, AddressMode::IMPLIED, "txs"}));
    instructionMap.insert(make_pair(0xE6, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "inc"}));
    instructionMap.insert(make_pair(0xF6, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE_X, "inc"}));
    instructionMap.insert(make_pair(0xEE, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "inc"}));
    instructionMap.insert(make_pair(0xFE, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE_X, "inc"}));

    instructionMap.insert(make_pair(0xC9, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::IMMEDIATE, "cmp"}));
    instructionMap.insert(make_pair(0xC5, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "cmp"}));
    instructionMap.insert(make_pair(0xD5, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE_X, "cmp"}));
    instructionMap.insert(make_pair(0xCD, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "cmp"}));
    instructionMap.insert(make_pair(0xDD, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE_X, "cmp"}));
    instructionMap.insert(make_pair(0xD9, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE_Y, "cmp"}));
    instructionMap.insert(make_pair(0xC1, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::INDIRECT_X, "cmp"}));
    instructionMap.insert(make_pair(0xD1, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::INDIRECT_Y, "cmp"}));

    instructionMap.insert(make_pair(0xC0, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::IMMEDIATE, "cpy"}));
    instructionMap.insert(make_pair(0xC4, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "cpy"}));
    instructionMap.insert(make_pair(0xCC, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "cpy"}));

    instructionMap.insert(make_pair(0xE0, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::IMMEDIATE, "cpx"}));
    instructionMap.insert(make_pair(0xE4, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "cpx"}));
    instructionMap.insert(make_pair(0xEC, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "cpx"}));
    instructionMap.insert(make_pair(0x24, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "bit"}));
    instructionMap.insert(make_pair(0x2C, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "bit"}));

    instructionMap.insert(make_pair(0x0A, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ACCUMULATOR, "asl"}));
    instructionMap.insert(make_pair(0x06, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE, "asl"}));
    instructionMap.insert(make_pair(0x16, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ZERO_PAGE_X, "asl"}));
    instructionMap.insert(make_pair(0x0E, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE, "asl"}));
    instructionMap.insert(make_pair(0x1E, Instruction{(InstructionProcedure)disassemble_MultiByteInstr, AddressMode::ABSOLUTE_X, "asl"}));
    instructionMap.insert(make_pair(0x0, Instruction{(InstructionProcedure)disassemble_brk, AddressMode::IMPLIED, "brk"}));

    /*
    #pragma region AND
        instructionMap.insert(make_pair(0x29, Instruction{(instructionPointer)AND, AddressMode::IMMEDIATE}));
        instructionMap.insert(make_pair(0x25, Instruction{(instructionPointer)AND, AddressMode::ZERO_PAGE}));
        instructionMap.insert(make_pair(0x35, Instruction{(instructionPointer)AND, AddressMode::ZERO_PAGE_X}));
        instructionMap.insert(make_pair(0x2D, Instruction{(instructionPointer)AND, AddressMode::ABSOLUTE}));
        instructionMap.insert(make_pair(0x3D, Instruction{(instructionPointer)AND, AddressMode::ABSOLUTE_X}));
        instructionMap.insert(make_pair(0x39, Instruction{(instructionPointer)AND, AddressMode::ABSOLUTE_Y}));
        instructionMap.insert(make_pair(0x21, Instruction{(instructionPointer)AND, AddressMode::INDIRECT_X}));
        instructionMap.insert(make_pair(0x31, Instruction{(instructionPointer)AND, AddressMode::INDIRECT_Y}));
    #pragma endregion

    #pragma region ORA
        instructionMap.insert(make_pair(0x09, Instruction{(instructionPointer)ORA, AddressMode::IMMEDIATE}));
        instructionMap.insert(make_pair(0x05, Instruction{(instructionPointer)ORA, AddressMode::ZERO_PAGE}));
        instructionMap.insert(make_pair(0x15, Instruction{(instructionPointer)ORA, AddressMode::ZERO_PAGE_X}));
        instructionMap.insert(make_pair(0x0D, Instruction{(instructionPointer)ORA, AddressMode::ABSOLUTE}));
        instructionMap.insert(make_pair(0x1D, Instruction{(instructionPointer)ORA, AddressMode::ABSOLUTE_X}));
        instructionMap.insert(make_pair(0x19, Instruction{(instructionPointer)ORA, AddressMode::ABSOLUTE_Y}));
        instructionMap.insert(make_pair(0x01, Instruction{(instructionPointer)ORA, AddressMode::INDIRECT_X}));
        instructionMap.insert(make_pair(0x11, Instruction{(instructionPointer)ORA, AddressMode::INDIRECT_Y}));
    #pragma endregion

    #pragma region ROL/ROR
        instructionMap.insert(make_pair(0x2A, Instruction{(instructionPointer)ROL, AddressMode::ACCUMULATOR}));
        instructionMap.insert(make_pair(0x26, Instruction{(instructionPointer)ROL, AddressMode::ZERO_PAGE}));
        instructionMap.insert(make_pair(0x36, Instruction{(instructionPointer)ROL, AddressMode::ZERO_PAGE_X}));
        instructionMap.insert(make_pair(0x2E, Instruction{(instructionPointer)ROL, AddressMode::ABSOLUTE}));
        instructionMap.insert(make_pair(0x3E, Instruction{(instructionPointer)ROL, AddressMode::ABSOLUTE_X}));

        instructionMap.insert(make_pair(0x6A, Instruction{(instructionPointer)ROR, AddressMode::ACCUMULATOR}));
        instructionMap.insert(make_pair(0x66, Instruction{(instructionPointer)ROR, AddressMode::ZERO_PAGE}));
        instructionMap.insert(make_pair(0x76, Instruction{(instructionPointer)ROR, AddressMode::ZERO_PAGE_X}));
        instructionMap.insert(make_pair(0x6E, Instruction{(instructionPointer)ROR, AddressMode::ABSOLUTE}));
        instructionMap.insert(make_pair(0x7E, Instruction{(instructionPointer)ROR, AddressMode::ABSOLUTE_X}));
    #pragma endregion




    #pragma endregion

    #pragma region bitshift
        instructionMap.insert(make_pair(0x4A, Instruction{(instructionPointer)LSR, AddressMode::ACCUMULATOR}));
        instructionMap.insert(make_pair(0x46, Instruction{(instructionPointer)LSR, AddressMode::ZERO_PAGE}));
        instructionMap.insert(make_pair(0x56, Instruction{(instructionPointer)LSR, AddressMode::ZERO_PAGE_X}));
        instructionMap.insert(make_pair(0x4E, Instruction{(instructionPointer)LSR, AddressMode::ABSOLUTE}));
        instructionMap.insert(make_pair(0x5E, Instruction{(instructionPointer)LSR, AddressMode::ABSOLUTE_X}));

        instructionMap.insert(make_pair(0x0A, Instruction{(instructionPointer)ASL, AddressMode::ACCUMULATOR}));
        instructionMap.insert(make_pair(0x06, Instruction{(instructionPointer)ASL, AddressMode::ZERO_PAGE}));
        instructionMap.insert(make_pair(0x16, Instruction{(instructionPointer)ASL, AddressMode::ZERO_PAGE_X}));
        instructionMap.insert(make_pair(0x0E, Instruction{(instructionPointer)ASL, AddressMode::ABSOLUTE}));
        instructionMap.insert(make_pair(0x1E, Instruction{(instructionPointer)ASL, AddressMode::ABSOLUTE_X}));
    #pragma endregion

    #pragma region XOR
        instructionMap.insert(make_pair(0x49, Instruction{(instructionPointer)EOR, AddressMode::IMMEDIATE}));
        instructionMap.insert(make_pair(0x45, Instruction{(instructionPointer)EOR, AddressMode::ZERO_PAGE}));
        instructionMap.insert(make_pair(0x55, Instruction{(instructionPointer)EOR, AddressMode::ZERO_PAGE_X}));
        instructionMap.insert(make_pair(0x4D, Instruction{(instructionPointer)EOR, AddressMode::ABSOLUTE}));
        instructionMap.insert(make_pair(0x5D, Instruction{(instructionPointer)EOR, AddressMode::ABSOLUTE_X}));
        instructionMap.insert(make_pair(0x59, Instruction{(instructionPointer)EOR, AddressMode::ABSOLUTE_Y}));
        instructionMap.insert(make_pair(0x41, Instruction{(instructionPointer)EOR, AddressMode::INDIRECT_X}));
        instructionMap.insert(make_pair(0x51, Instruction{(instructionPointer)EOR, AddressMode::INDIRECT_Y}));
    #pragma endregion

    #pragma region DEC
        instructionMap.insert(make_pair(0xCA, Instruction{(instructionPointer)DEX, AddressMode::IMPLIED}));
        instructionMap.insert(make_pair(0x88, Instruction{(instructionPointer)DEY, AddressMode::IMPLIED}));

        instructionMap.insert(make_pair(0xC6, Instruction{(instructionPointer)DEC, AddressMode::ZERO_PAGE}));
        instructionMap.insert(make_pair(0xD6, Instruction{(instructionPointer)DEC, AddressMode::ZERO_PAGE_X}));
        instructionMap.insert(make_pair(0xCE, Instruction{(instructionPointer)DEC, AddressMode::ABSOLUTE}));
        instructionMap.insert(make_pair(0xDE, Instruction{(instructionPointer)DEC, AddressMode::ABSOLUTE_X}));
    #pragma endregion
    */

    // #pragma region INC
    //
    //     instructionMap.insert(make_pair(0xC8, Instruction{(instructionPointer)INY, AddressMode::IMPLIED}));

    //     instructionMap.insert(make_pair(0xE6, Instruction{(instructionPointer)INC, AddressMode::ZERO_PAGE}));
    //     instructionMap.insert(make_pair(0xF6, Instruction{(instructionPointer)INC, AddressMode::ZERO_PAGE_X}));
    //     instructionMap.insert(make_pair(0xEE, Instruction{(instructionPointer)INC, AddressMode::ABSOLUTE}));
    //     instructionMap.insert(make_pair(0xFE, Instruction{(instructionPointer)INC, AddressMode::ABSOLUTE_X}));
    // #pragma endregion

    // #pragma region Clear/set Flags
    //     instructionMap.insert(make_pair(0x18, Instruction{(instructionPointer)CLC, AddressMode::IMPLIED})); //"implied"

    //     instructionMap.insert(make_pair(0x38, Instruction{(instructionPointer)SEC, AddressMode::IMPLIED}));

    //     instructionMap.insert(make_pair(0xD8, Instruction{(instructionPointer)CLD, AddressMode::IMPLIED}));

    //     instructionMap.insert(make_pair(0xF8, Instruction{(instructionPointer)SED, AddressMode::IMPLIED}));

    //     instructionMap.insert(make_pair(0x78, Instruction{(instructionPointer)SEI, AddressMode::IMPLIED}));

    //     instructionMap.insert(make_pair(0x58, Instruction{(instructionPointer)CLI, AddressMode::IMPLIED}));

    //     instructionMap.insert(make_pair(0xB8, Instruction{(instructionPointer)CLV, AddressMode::IMPLIED}));

    //     instructionMap.insert(make_pair(0x40, Instruction{(instructionPointer)RTI, AddressMode::IMPLIED}));
    // #pragma endregion

    // #pragma region JMP
    //     instructionMap.insert(make_pair(0x4C, Instruction{(instructionPointer)JMP, AddressMode::ABSOLUTE}));
    //     instructionMap.insert(make_pair(0x6C, Instruction{(instructionPointer)JMP, AddressMode::INDIRECT}));
    // #pragma endregion

    /*
    #pragma region Compare
        instructionMap.insert(make_pair(0xC9, Instruction{(instructionPointer)CMP, AddressMode::IMMEDIATE}));
        instructionMap.insert(make_pair(0xC5, Instruction{(instructionPointer)CMP, AddressMode::ZERO_PAGE}));
        instructionMap.insert(make_pair(0xD5, Instruction{(instructionPointer)CMP, AddressMode::ZERO_PAGE_X}));
        instructionMap.insert(make_pair(0xCD, Instruction{(instructionPointer)CMP, AddressMode::ABSOLUTE}));
        instructionMap.insert(make_pair(0xDD, Instruction{(instructionPointer)CMP, AddressMode::ABSOLUTE_X}));
        instructionMap.insert(make_pair(0xD9, Instruction{(instructionPointer)CMP, AddressMode::ABSOLUTE_Y}));
        instructionMap.insert(make_pair(0xC1, Instruction{(instructionPointer)CMP, AddressMode::INDIRECT_X}));
        instructionMap.insert(make_pair(0xD1, Instruction{(instructionPointer)CMP, AddressMode::INDIRECT_Y}));

        instructionMap.insert(make_pair(0xC0, Instruction{(instructionPointer)CPY, AddressMode::IMMEDIATE}));
        instructionMap.insert(make_pair(0xC4, Instruction{(instructionPointer)CPY, AddressMode::ZERO_PAGE}));
        instructionMap.insert(make_pair(0xCC, Instruction{(instructionPointer)CPY, AddressMode::ABSOLUTE}));

        instructionMap.insert(make_pair(0xE0, Instruction{(instructionPointer)CPX, AddressMode::IMMEDIATE}));
        instructionMap.insert(make_pair(0xE4, Instruction{(instructionPointer)CPX, AddressMode::ZERO_PAGE}));
        instructionMap.insert(make_pair(0xEC, Instruction{(instructionPointer)CPX, AddressMode::ABSOLUTE}));

        instructionMap.insert(make_pair(0x24, Instruction{(instructionPointer)BIT, AddressMode::ZERO_PAGE}));
        instructionMap.insert(make_pair(0x2C, Instruction{(instructionPointer)BIT, AddressMode::ABSOLUTE}));

    #pragma endregion
    */
    // #pragma region Conditional Branching
    //     instructionMap.insert(make_pair(0xF0, Instruction{(instructionPointer)BEQ, AddressMode::RELATIVE}));

    //     instructionMap.insert(make_pair(0xD0, Instruction{(instructionPointer)BNE, AddressMode::RELATIVE}));

    //     instructionMap.insert(make_pair(0x90, Instruction{(instructionPointer)BCC, AddressMode::RELATIVE}));

    //     instructionMap.insert(make_pair(0xB0, Instruction{(instructionPointer)BCS, AddressMode::RELATIVE}));

    //     instructionMap.insert(make_pair(0x10, Instruction{(instructionPointer)BPL, AddressMode::RELATIVE}));

    //     instructionMap.insert(make_pair(0x30, Instruction{(instructionPointer)BMI, AddressMode::RELATIVE}));

    //     instructionMap.insert(make_pair(0x50, Instruction{(instructionPointer)BVC, AddressMode::RELATIVE}));

    //     instructionMap.insert(make_pair(0x70, Instruction{(instructionPointer)BVS, AddressMode::RELATIVE}));
    // #pragma endregion

    // #pragma region Subroutine
    //     instructionMap.insert(make_pair(0x20, Instruction{(instructionPointer)JSR, AddressMode::ABSOLUTE}));

    //     instructionMap.insert(make_pair(0x60, Instruction{(instructionPointer)RTS, AddressMode::IMPLIED}));
    // #pragma endregion

    /*
    #pragma region Pull register from stack
        instructionMap.insert(make_pair(0x28, Instruction{(instructionPointer)PLP, AddressMode::IMPLIED}));

        instructionMap.insert(make_pair(0x08, Instruction{(instructionPointer)PHP, AddressMode::IMPLIED}));

        instructionMap.insert(make_pair(0x68, Instruction{(instructionPointer)PLA, AddressMode::IMPLIED}));

        instructionMap.insert(make_pair(0x48, Instruction{(instructionPointer)PHA, AddressMode::IMPLIED}));
    #pragma endregion

    #pragma region Transfer
        instructionMap.insert(make_pair(0xAA, Instruction{(instructionPointer)TAX, AddressMode::IMPLIED}));

        instructionMap.insert(make_pair(0x8A, Instruction{(instructionPointer)TXA, AddressMode::IMPLIED}));

        instructionMap.insert(make_pair(0x9A, Instruction{(instructionPointer)TXS, AddressMode::IMPLIED}));

        instructionMap.insert(make_pair(0xBA, Instruction{(instructionPointer)TSX, AddressMode::IMPLIED}));

        instructionMap.insert(make_pair(0x98, Instruction{(instructionPointer)TYA, AddressMode::IMPLIED}));

        instructionMap.insert(make_pair(0xA8, Instruction{(instructionPointer)TAY, AddressMode::IMPLIED}));
    #pragma endregion
        instructionMap.insert(make_pair(0x00, Instruction{(instructionPointer)BRK, AddressMode::IMPLIED}));
        instructionMap.insert(make_pair(0xea, Instruction{(instructionPointer)NOP, AddressMode::IMPLIED}));
    */
    /*
    instructionMap.insert(std::make_pair(0xA9, Instruction{(instructionPointer)LDA, AddressMode::IMMEDIATE}));
    instructionMap.insert(std::make_pair(0xA5, Instruction{(instructionPointer)LDA, AddressMode::ZERO_PAGE}));
    instructionMap.insert(std::make_pair(0xB5, Instruction{(instructionPointer)LDA, AddressMode::ZERO_PAGE_X}));
    instructionMap.insert(std::make_pair(0xAD, Instruction{(instructionPointer)LDA, AddressMode::ABSOLUTE}));
    instructionMap.insert(std::make_pair(0xBD, Instruction{(instructionPointer)LDA, AddressMode::ABSOLUTE_X}));
    instructionMap.insert(std::make_pair(0xB9, Instruction{(instructionPointer)LDA, AddressMode::ABSOLUTE_Y}));
    instructionMap.insert(std::make_pair(0xA1, Instruction{(instructionPointer)LDA, AddressMode::INDIRECT_X}));
    instructionMap.insert(std::make_pair(0xB1, Instruction{(instructionPointer)LDA, AddressMode::INDIRECT_Y}));

    instructionMap.insert(std::make_pair(0xA2, Instruction{(instructionPointer)LDX, AddressMode::IMMEDIATE}));
    instructionMap.insert(std::make_pair(0xA6, Instruction{(instructionPointer)LDX, AddressMode::ZERO_PAGE}));
    instructionMap.insert(std::make_pair(0xb6, Instruction{(instructionPointer)LDX, AddressMode::ZERO_PAGE_Y}));
    instructionMap.insert(std::make_pair(0xAe, Instruction{(instructionPointer)LDX, AddressMode::ABSOLUTE}));
    instructionMap.insert(std::make_pair(0xbe, Instruction{(instructionPointer)LDX, AddressMode::ABSOLUTE_Y}));

    instructionMap.insert(std::make_pair(0xA0, Instruction{(instructionPointer)LDY, AddressMode::IMMEDIATE}));
    instructionMap.insert(std::make_pair(0xA4, Instruction{(instructionPointer)LDY, AddressMode::ZERO_PAGE}));
    instructionMap.insert(std::make_pair(0xb4, Instruction{(instructionPointer)LDY, AddressMode::ZERO_PAGE_X}));
    instructionMap.insert(std::make_pair(0xAC, Instruction{(instructionPointer)LDY, AddressMode::ABSOLUTE}));
    instructionMap.insert(std::make_pair(0xBC, Instruction{(instructionPointer)LDY, AddressMode::ABSOLUTE_X}));

    instructionMap.insert(std::make_pair(0x4C, Instruction{(instructionPointer)JMP, AddressMode::ABSOLUTE}));
    instructionMap.insert(std::make_pair(0x40, Instruction{(instructionPointer)RTI, AddressMode::ABSOLUTE}));

    instructionMap.insert(std::make_pair(0xF0, Instruction{(instructionPointer)BEQ, AddressMode::RELATIVE}));
    instructionMap.insert(std::make_pair(0xD0, Instruction{(instructionPointer)BNE, AddressMode::RELATIVE}));

    instructionMap.insert(std::make_pair(0x30, Instruction{(instructionPointer)BMI, AddressMode::RELATIVE}));
    instructionMap.insert(std::make_pair(0x10, Instruction{(instructionPointer)BPL, AddressMode::RELATIVE}));

    instructionMap.insert(std::make_pair(0x90, Instruction{(instructionPointer)BCC, AddressMode::RELATIVE}));
    instructionMap.insert(std::make_pair(0xB0, Instruction{(instructionPointer)BCS, AddressMode::RELATIVE}));
    */
}
Instruction GetInstruction(uint8_t opcode)
{
    return instructionMap.at(opcode);
}
bool InstructionValid(uint8_t opcode)
{
    return instructionMap.find(opcode) != instructionMap.end();
}