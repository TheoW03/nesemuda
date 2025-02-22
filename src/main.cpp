#include <iostream>
#include <RomUtil.h>
#include <Disasm.h>
int main(int argc, char const *argv[])
{
    /* code */
    auto parsed_rom = load_rom(file_tobyte_vector("./games/TestRom1.nes"));
    init(parsed_rom);
    return 0;
}
