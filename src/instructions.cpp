#include <instruction.h>
#include <util.h>

Bus::Bus(std::vector<uint8_t> instr, uint16_t pc_starting)
{
    this->instr = instr;
    this->reset_vector = pc_starting;
}
void Bus::fill_instr(uint16_t new_pc)
{

    if (instr[(new_pc - reset_vector)] == 0x82)
    {
        return;
    }
    this->pc = new_pc;

    stored_instructions[0] = instr[(pc + 1) - reset_vector];
    stored_instructions[1] = instr[(pc - reset_vector)];
    instr[this->pc - reset_vector] = 0x82;
    instr[(pc + 1) - reset_vector] = 0x82;
    pc++;
}
uint8_t Bus::get_instr()
{
    uint8_t current_instruction = stored_instructions[1];
    stored_instructions[1] = stored_instructions[0];
    pc++;
    stored_instructions[0] = instr[this->pc - reset_vector];
    instr[this->pc - reset_vector] = 0x82;
    return current_instruction;
}
uint16_t Bus::get_pc()
{
    return this->pc;
}
Header::Header(NESHeader header)
{
    this->header = header;
}

std::string Header::disassm()
{
    std::string str = ".SEGMENT \"HEADER\" \n";
    str += "\t   .byte $4E, $45, $53, $1A  \n ";
    str += "\t   .byte " + std::to_string(header.prg_size) + "\n";
    str += "\t   .byte " + std::to_string(header.chr_size) + "\n";
    str += "\t   .byte " + byteToHex8(header.flag6.val) + "," + byteToHex8(header.flag7.mapper_upper) + "\n";
    str += "\t   .byte " + byteToHex8(header.flag7.val) + "\n";
    str += "\t   .byte " + byteToHex8(header.flag8) + "\n";
    str += "\t   .byte " + byteToHex8(header.flag9.val) + "\n";

    // std::stringstream stream;
    // stream << std::hex << header.flag6.mapper_lower;
    // std::string result(stream.str());
    // str += "\t   .byte " + std::to_string(header.flag6.mapper_lower) ", " + "\n";

    return str;
}

instr::instr()
{
}

instr::instr(uint16_t pc)
{
    this->pc = pc;
}

Lda::Lda()
{
}

Lda::Lda(AddressMode addressMode, std::vector<uint8_t> opcodes, uint16_t pc) : instr(pc)
{
    this->opcodes = opcodes;
    this->addressMode = addressMode;
    this->pc = pc;
    // Instr::pc = pc;
}

std::string Lda::disassm()
{
    std::string instr = "lda ";
    if (addressMode == AddressMode::IMMEDIATE)
    {
        instr += "#" + std::to_string(opcodes[0]) + "\n";
    }
    else if (addressMode == AddressMode::ZERO_PAGE)
    {
        instr += byteToHex8(opcodes[0]) + "\n";
    }
    else if (addressMode == AddressMode::ZERO_PAGE_X)
    {
        instr += byteToHex8(opcodes[0]) + ", X \n";
    }
    else if (addressMode == AddressMode::ABSOLUTE)
    {
        instr += byteToHex16(opcodes[1] << 8 | opcodes[0]) + " \n";
    }
    else if (addressMode == AddressMode::ABSOLUTE_X)
    {
        instr += byteToHex16(opcodes[1] << 8 | opcodes[0]) + ", X \n";
    }
    else if (addressMode == AddressMode::ABSOLUTE_Y)
    {
        instr += byteToHex16(opcodes[1] << 8 | opcodes[0]) + ", Y \n";
    }
    else if (addressMode == AddressMode::INDIRECT_X)
    {
        instr += "(" + byteToHex16(opcodes[0]) + ", X )\n";
    }
    else if (addressMode == AddressMode::INDIRECT_Y)
    {
        instr += "(" + byteToHex16(opcodes[0]) + "), Y \n";
    }
    return instr;
}
Label::Label(std::string name, uint16_t pc) : instr(pc)
{
    this->name = name;
    this->pc = pc;
}
std::string Label::disassm()
{
    return name + ": \n";
}

Jmp::Jmp()
{
}

Jmp::Jmp(AddressMode addressMode, std::string lable, uint16_t pc) : instr(pc)
{
    this->lable_name = lable;
    this->addressMode = addressMode;
    this->pc = pc;
}

Jmp::Jmp(AddressMode addressMode, std::vector<uint8_t> opcodes, uint16_t pc) : instr(pc)
{
    this->opcodes = opcodes;
    this->addressMode = addressMode;
    this->pc = pc;
}

std::string Jmp::disassm()
{
    return "jmp " + lable_name + "\n";
}

Rti::Rti(AddressMode addressMode, uint16_t pc) : instr(pc)
{
    this->addressMode = addressMode;
}
std::string Rti::disassm()
{
    return "rti \n";
}