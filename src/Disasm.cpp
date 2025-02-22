#include <RomUtil.h>

#include <instruction.h>

void init(NESRom nes)
{
    Header h = Header(nes.header);
    std::cout << h.disassm() << std::endl;
}