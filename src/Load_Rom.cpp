#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <optional>
#include <cstdint>
#include <RomUtil.h>

#define PRG_ROM_SIZE 16384
#define CHR_ROM_SIZE 8192

std::vector<uint8_t> file_tobyte_vector(std::string file_name)
{
    std::vector<uint8_t> instructions;
    std::ifstream infile(file_name, std::ios::binary); // Open the file for reading
    std::string line;
    while (infile)
    {
        uint8_t a = (uint8_t)infile.get();
        instructions.push_back(a);
    }

    return instructions;
}
NESRom load_rom(std::vector<uint8_t> instructions)
{

    NESHeader nes_header;
    memcpy(&nes_header, instructions.data(), sizeof(NESHeader));
    if (                                 //
        (nes_header.ident[0] != 'N'      //
         && nes_header.ident[1] != 'E'   //
         && nes_header.ident[2] != 'S'   //
         && nes_header.ident[3] != 0x1a) // all man style should be the default in the VS code formatiro
        || nes_header.flag7.inesverif == 0xc)
    {
        std::cout << "TetroidDisasm: this isnt a iNES version 1.0 header" << std::endl;
        exit(EXIT_FAILURE);
    }

    return NESRom();
}