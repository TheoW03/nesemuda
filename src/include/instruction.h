#include <iostream>
#include <vector>
#include <RomUtil.h>
#include <stdint.h>
#include <map>

#ifndef ADDRESS_MODE_H
#define ADDRESS_MODE_H
enum AddressMode
{
    ACCUMULATOR,
    ABSOLUTE,
    ABSOLUTE_Y,
    ABSOLUTE_X,
    ZERO_PAGE,
    ZERO_PAGE_X,
    ZERO_PAGE_Y,
    IMMEDIATE,
    INDIRECT,
    INDIRECT_X,
    INDIRECT_Y,
    RELATIVE,
    IMPLIED
};
#endif

#ifndef BUS_H
#define BUS_H
class Bus
{
public:
    uint8_t stored_instructions[2];
    std::vector<uint8_t> instr;
    uint16_t reset_vector;
    uint16_t pc;
    Bus(std::vector<uint8_t> instr, uint16_t pc_starting);
    uint8_t get_instr();
    uint16_t get_pc();
    void fill_instr(uint16_t new_pc);
};
#endif

#ifndef DIS_ASM_STATE_H
struct DisAsmState
{
    Bus bus;
    std::map<uint16_t, std::string> known_lables;
};
#endif
#ifndef HEADER_DISASM_H
#define HEADER_DISASM_H
class Header
{
public:
    NESHeader header;
    Header(NESHeader header);
    std::string disassm();
};
#endif
#ifndef INSTR_H
#define INSTR_H

class instr
{
public:
    uint16_t pc;
    instr();
    instr(uint16_t pc);
    virtual std::string disassm() = 0;
};

#endif
#ifndef LABEL_H
#define LABEL_H

class Label : public instr
{
public:
    std::string name;
    Label(std::string name);
    std::string disassm() override;
};
#endif

#ifndef LDA_H
#define LDA_H

class Lda : public instr
{
public:
    std::vector<uint8_t> opcodes;
    uint16_t pc;
    AddressMode addressMode;
    Lda();
    Lda(AddressMode addressMode, std::vector<uint8_t> opcodes, uint16_t pc);
    std::string disassm() override;
};

#endif

#ifndef PRGRAM_H
#define PROGRAM_H
class Program
{
public:
    Header header;
    std::vector<instr> instrunctions;

    Program(Header header, std::vector<instr> instrunctions);
    std::string disassm();
};
#endif