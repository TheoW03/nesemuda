#include <stdint.h>
#include <vector>
#include <iostream>
// easier to understand over doing bytes and bit operations
#ifndef NES_HEADER_H
#define NES_HEADER_H

typedef uint8_t byte_t;

struct NESHeader
{
    byte_t ident[4]; // should be the words "NES 0x1a"
    byte_t prg_size; // size of PRG
    byte_t chr_size; // size of chr
    union
    {
        struct
        {
            unsigned mapper_lower : 4; // lower bits of mapper
            unsigned four_screen : 1;  // if 4 screen
            unsigned trainer : 1;      // trainer. Ie the PRG is a 512 offset
            unsigned battery : 1;      // for zelda (it used a battery to save )
            unsigned vertical : 1;     // if vertical
        };
        byte_t val;
    } flag6;

    union
    {
        struct
        {
            unsigned mapper_upper : 4; // upper bits of mapper
            unsigned inesverif : 4;    // 0xc to verify if its ines 1.0 format
        };
        byte_t val;
    } flag7;

    byte_t flag8;

    union
    {
        struct
        {
            unsigned color_encoding : 1; // NTSC vs pal
            unsigned padding : 7;
        };
        byte_t val;
    } flag9;
};
#endif

#ifndef NES_ROM_h
#define NES_ROM_h

struct NESRom
{

    struct NESHeader header;
    std::vector<uint8_t> prg_rom;
    std::vector<uint8_t> chr_rom;
};

#endif

std::vector<uint8_t>
file_tobyte_vector(std::string file_name);

NESRom load_rom(std::vector<uint8_t> instructions);