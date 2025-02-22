#include <RomUtil.h>
#include <fstream>

#include <instruction.h>
#include <memory>
#include <map>

std::vector<std::shared_ptr<instr>> computer(Bus bus, std::map<uint16_t, std::string> known_lables)
{
    std::vector<std::shared_ptr<instr>> c;

    bool end = false;
    while (!end)
    {
        if (known_lables.find(bus.get_pc()) != known_lables.end())
        {
            c.push_back(std::make_shared<Label>(known_lables[bus.get_pc()]));
        }
        uint8_t instr = bus.get_instr();

        if (instr == 0xa9)
        {
            std::cout << "lda" << std::endl;
            std::vector<uint8_t> opcodes;
            opcodes.push_back({bus.get_instr()});
            c.push_back(std::make_shared<Lda>(AddressMode::IMMEDIATE, opcodes));
        }
        else if (instr == 0x0)
        {
            end = true;
        }
    }
    return c;
}

void init(NESRom nes)
{
    Header h = Header(nes.header);
    uint16_t pc_start = nes.prg_rom[0xfffd - 0x8000] << 8 | nes.prg_rom[0xfffc - 0x8000];
    uint16_t nmi = nes.prg_rom[0xfffb - 0x8000] << 8 | nes.prg_rom[0xfffa - 0x8000];

    Bus bus = Bus(nes.prg_rom, pc_start);
    printf("pc: %x \n", nmi);
    bus.fill_instr(pc_start);
    std::map<uint16_t, std::string> known_lables;
    known_lables[pc_start] = "reset";
    known_lables[nmi] = "nmi";
    auto prg = computer(bus, known_lables);
    std::cout << h.disassm() << std::endl;
    std::ofstream outputFile("Out.s");

    outputFile << h.disassm();
    outputFile << ".SEGMENT \"VECTORS\" \n";

    outputFile << ".addr reset \n";
    outputFile << ".addr nmi \n";

    outputFile << ".SEGMENT \"STARTUP\" \n";
    for (int i = 0; i < prg.size(); i++)
    {
        std::cout << prg[i]->disassm() << std::endl;
        outputFile << prg[i]->disassm();
    }

    outputFile.close();
}