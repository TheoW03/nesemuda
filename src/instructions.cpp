#include <instruction.h>
#include <util.h>

Bus::Bus(std::vector<uint8_t> instr, uint16_t pc_starting)
{
    this->instr = instr;
    this->reset_vector = pc_starting;
}
void Bus::fill_instr(uint16_t new_pc)
{
    this->pc = new_pc;

    stored_instructions[0] = instr[(pc + 1) - reset_vector];
    stored_instructions[1] = instr[(pc - reset_vector)];
}
uint8_t Bus::get_instr()
{
    uint8_t current_instruction = stored_instructions[1];
    stored_instructions[1] = stored_instructions[0];
    pc++;
    stored_instructions[0] = instr[this->pc - reset_vector];
    // printf("%d \n", this->pc - reset_vector);
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
    str += "\t   .byte " + byteToHex(header.flag6.val) + "," + byteToHex(header.flag7.mapper_upper) + "\n";
    str += "\t   .byte " + byteToHex(header.flag7.val) + "\n";
    str += "\t   .byte " + byteToHex(header.flag8) + "\n";
    str += "\t   .byte " + byteToHex(header.flag9.val) + "\n";

    // std::stringstream stream;
    // stream << std::hex << header.flag6.mapper_lower;
    // std::string result(stream.str());
    // str += "\t   .byte " + std::to_string(header.flag6.mapper_lower) ", " + "\n";

    return str;
}

instr::instr()
{
}

Lda::Lda()
{
}

Lda::Lda(AddressMode addressMode, std::vector<uint8_t> opcodes)
{
    this->opcodes = opcodes;
    this->addressMode = addressMode;
}

std::string Lda::disassm()
{
    std::string instr = "lda ";
    if (addressMode == AddressMode::IMMEDIATE)
    {
        instr += "#" + std::to_string(opcodes[0]) + "\n";
    }
    return instr;
}
Label::Label(std::string name)
{
    this->name = name;
}
std::string Label::disassm()
{
    return name + ": \n";
}