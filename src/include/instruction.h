#include <iostream>
#include <vector>
#include <RomUtil.h>

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
    instr(std::vector<uint8_t> opcodes);
    virtual std::string disassm() = 0;
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