#include <instruction.h>

Header::Header(NESHeader header)
{
    this->header = header;
}

std::string Header::disassm()
{
    std::string str = ".SEGMENT \"HEADER\" \n";

    return str;
}
