#include <RomUtil.h>
#include <fstream>
#include <instruction_map.h>
// #include <instruction.h>
#include <memory>
#include <map>

std::vector<std::shared_ptr<instr>> computer(DisAsmState state)
{
    std::vector<std::shared_ptr<instr>> c;

    bool end = false;
    initializeInstructionMap();
    while (!end)
    {
        if (state.known_lables.find(state.bus.get_pc() - 1) != state.known_lables.end())
        {
            c.push_back(std::make_shared<Label>(state.known_lables[state.bus.get_pc() - 1]));
        }
        uint8_t instr = state.bus.get_instr();

        if (instr == 0x0 || !InstructionValid(instr))
        {
            std::cout << "instruction not valid  " << instr << std::endl;
            printf("%x \n", instr);
            end = true;
            break;
        }
        auto current_instr = GetInstruction(instr);
        auto disassmble = current_instr.i(current_instr.addressmode, state);
        c.push_back(disassmble);
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
    auto prg = computer({bus, known_lables});
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