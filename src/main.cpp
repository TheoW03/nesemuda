#include <iostream>
#include <RomUtil.h>
#include <Disasm.h>
#include <util.h>
#include <cli.h>

int main(int argc, char const *argv[])
{

    std::vector<std::string> args;

    for (int i = 1; i < argc; i++)
    {
        args.push_back(argv[i]);
    }
    auto p = parse_cmd(args);
    /* code */
    std::cout << p.files << std::endl;
    auto parsed_rom = load_rom(file_tobyte_vector(p.files));
    init(parsed_rom, p.output_files);
    // std::cout << byteToHex16(0x8000) << std::endl;
    // std::cout << byteToHex(10) << std::endl;
    return 0;
}
