#include <instruction.h>
#include <util.h>

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
