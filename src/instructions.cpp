#include <instruction.h>
#include <util.h>
#include <instruction_map.h>

Header::Header(NESHeader header)
{
    this->header = header;
}

Ldx::Ldx()
{
}

Ldx::Ldx(AddressMode addressMode, std::vector<uint8_t> opcodes, uint16_t pc) : instr(pc)
{
    this->addressMode = addressMode;
    this->opcodes = opcodes;
    this->pc = pc;
}
std::string Ldx::disassm()
{
    std::string instr = "ldx ";
    if (addressMode == AddressMode::IMMEDIATE)
    {
        instr += "#" + std::to_string(opcodes[0]) + "\n";
    }
    else if (addressMode == AddressMode::ZERO_PAGE)
    {
        instr += byteToHex8(opcodes[0]) + "\n";
    }
    else if (addressMode == AddressMode::ZERO_PAGE_Y)
    {
        instr += byteToHex8(opcodes[0]) + ", Y \n";
    }
    else if (addressMode == AddressMode::ABSOLUTE)
    {
        instr += byteToHex16(opcodes[1] << 8 | opcodes[0]) + " \n";
    }
    else if (addressMode == AddressMode::ABSOLUTE_Y)
    {
        instr += byteToHex16(opcodes[1] << 8 | opcodes[0]) + ", Y \n";
    }
    return instr;
}

Ldy::Ldy()
{
}

Ldy::Ldy(AddressMode addressMode, std::vector<uint8_t> opcodes, uint16_t pc) : instr(pc)
{
    this->addressMode = addressMode;
    this->opcodes = opcodes;
    this->pc = pc;
}
std::string Ldy::disassm()
{
    std::string instr = "ldy ";
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
    return instr;
}

Jsr::Jsr()
{
}

Jsr::Jsr(AddressMode addressMode, InstrData data, uint16_t pc) : instr(pc)
{
    this->data = data;
    // this->lable_name = lable;
}
std::string Jsr::disassm()
{
    return "jsr " + this->data.label.value() + "\n";
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

MultiByteInstr::MultiByteInstr()
{
}

MultiByteInstr::MultiByteInstr(std::string instr_name, AddressMode address, InstrData data, uint16_t pc) : instr(pc)
{
    this->instr_name = instr_name;
    this->data = data;
    this->addressMode = address;
    this->pc = pc;
}

std::string MultiByteInstr::disassm()
{
    std::string instr = instr_name + " ";
    if (addressMode == AddressMode::ACCUMULATOR)
    {
        instr += "A \n";
    }
    else if (addressMode == AddressMode::IMMEDIATE)
    {
        instr += "#" + std::to_string(data.instr_data[0]) + "\n";
    }
    else if (addressMode == AddressMode::ZERO_PAGE)
    {
        instr += byteToHex8(data.instr_data[0]) + "\n";
    }
    else if (addressMode == AddressMode::ZERO_PAGE_X)
    {
        instr += byteToHex8(data.instr_data[0]) + ", X \n";
    }
    else if (addressMode == AddressMode::ABSOLUTE)
    {
        if (data.label.has_value())
        {
            instr += data.label.value() + "\n";
        }
        else
        {
            instr += byteToHex16(data.instr_data[1] << 8 | data.instr_data[0]) + " \n";
        }
    }
    else if (addressMode == AddressMode::ABSOLUTE_X)
    {
        if (data.label.has_value())
        {
            instr += data.label.value() + ", X\n";
        }
        else
        {
            instr += byteToHex16(data.instr_data[1] << 8 | data.instr_data[0]) + ",X \n";
        }
    }
    else if (addressMode == AddressMode::ABSOLUTE_Y)
    {
        if (data.label.has_value())
        {
            instr += data.label.value() + ", Y \n";
        }
        else
        {
            instr += byteToHex16(data.instr_data[1] << 8 | data.instr_data[0]) + ",Y \n";
        }
    }
    else if (addressMode == AddressMode::INDIRECT_X)
    {
        instr += "(" + byteToHex8(data.instr_data[0]) + ",X) \n";
        // instr += "(" + byteToHex16(opcodes[0]) + ", X)\n";
    }
    else if (addressMode == AddressMode::INDIRECT_Y)
    {
        instr += "(" + byteToHex8(data.instr_data[0]) + "), Y \n";
        // instr += "(" + byteToHex16(opcodes[0]) + "), Y \n";
    }
    return instr;
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
Macro::Macro(std::string name, uint16_t address, uint16_t pc) : instr(pc)
{
    this->name = name;
    this->addr = address;
}
std::string Macro::disassm()
{
    return ".define " + name + " " + byteToHex16(addr) + "\n";
}

std::string Label::disassm()
{
    return name + ": \n";
}

Jmp::Jmp()
{
}

Jmp::Jmp(AddressMode addressMode, InstrData data, uint16_t pc) : instr(pc)
{
    // this->lable_name = lable;
    this->addressMode = addressMode;
    this->data = data;
    this->pc = pc;
}

// Jmp::Jmp(AddressMode addressMode, std::vector<uint8_t> opcodes, uint16_t pc) : instr(pc)
// {
//     this->opcodes = opcodes;
//     this->addressMode = addressMode;
//     this->pc = pc;
// }

std::string Jmp::disassm()
{
    uint8_t lower_half = data.instr_data[0];
    uint8_t upper_half = data.instr_data[1];
    uint16_t adr = upper_half << 8 | lower_half;
    if (addressMode == AddressMode::ABSOLUTE)
    {
        if (data.label.has_value())
            return "jmp " + data.label.value() + "\n";
        else
            return "jmp " + byteToHex16(adr) + "\n";
    }
    else if (addressMode == AddressMode::INDIRECT)
    {

        if (data.label.has_value())
            return "jmp (" + data.label.value() + ")\n";
        else
            return "jmp (" + byteToHex16(adr) + ")";
    }
    return "";
}

Rti::Rti(AddressMode addressMode, uint16_t pc) : instr(pc)
{
    this->addressMode = addressMode;
}
std::string Rti::disassm()
{
    return "rti \n";
}

DefinedByte::DefinedByte(uint8_t byte, uint16_t pc) : instr(pc)
{
    this->byte = byte;
    this->pc = pc;
}

std::string DefinedByte::disassm()
{
    // return ".byte " + byteToHex8(std::get<0>(bytes)) + ", " + byteToHex8(std::get<1>(bytes)) + ", " + byteToHex8(std::get<2>(bytes)) + "," + byteToHex8(std::get<3>(bytes)) + "\n ";
    return ".byte " + byteToHex8(byte) + "\n";
}

oneByteInstr::oneByteInstr(std::string instr_name, uint16_t pc) : instr(pc)
{
    this->instr_name = instr_name;

    this->pc = pc;
}
std::string oneByteInstr::disassm()
{
    return this->instr_name + "\n";
}

BranchInstr::BranchInstr(std::string instr_name, std::string label, uint16_t pc) : instr(pc)
{
    this->instr_name = instr_name;
    this->label = label;
    this->pc = pc;
}

std::string BranchInstr::disassm()
{
    return instr_name + " " + label + "\n";
}
