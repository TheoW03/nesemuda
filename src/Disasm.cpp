#include <RomUtil.h>
#include <fstream>

#include <instruction.h>

void init(NESRom nes)
{
    Header h = Header(nes.header);
    std::ofstream outputFile("Out.s");
    std::cout << h.disassm() << std::endl;
    outputFile << h.disassm();
    outputFile.close();
}