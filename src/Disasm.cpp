#include <RomUtil.h>
#include <fstream>

#include <instruction.h>
#include <memory>
#include <map>

std::vector<std::shared_ptr<instr>> computer(Bus bus)
{
    std::vector<std::shared_ptr<instr>> c;

    std::map<uint16_t, std::string> known_lables;
    known_lables[0x8000] = "reset";
    known_lables[0x8002] = "nmi";

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
    Bus bus = Bus(nes.prg_rom, 0x8000);
    bus.fill_instr(0x8000);
    auto prg = computer(bus);
    std::cout << h.disassm() << std::endl;
    std::ofstream outputFile("Out.s");

    outputFile << h.disassm();
    outputFile << ".SEGMENT \"VECTORS\" \n";

    outputFile << ".SEGMENT \"STARTUP\" \n";
    for (int i = 0; i < prg.size(); i++)
    {
        std::cout << prg[i]->disassm() << std::endl;
        outputFile << prg[i]->disassm();
    }

    outputFile.close();
}