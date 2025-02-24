#include <RomUtil.h>
#include <fstream>
#include <instruction_map.h>
// #include <instruction.h>
#include <algorithm>
#include <memory>
#include <map>

std::vector<std::shared_ptr<instr>> computer(DisAsmState &state)
{
    std::vector<std::shared_ptr<instr>> c;

    bool end = false;
    initializeInstructionMap();
    while (!end)
    {
        if (state.known_lables.find(state.bus.get_pc() - 1) != state.known_lables.end() //
            && state.assembled.find(state.bus.get_pc() - 1) == state.assembled.end())
        {
            c.push_back(std::make_shared<Label>(state.known_lables[state.bus.get_pc() - 1], state.bus.get_pc() - 1));
            state.assembled.insert(std::make_pair(state.bus.get_pc() - 1, state.known_lables[state.bus.get_pc() - 1]));
            // state.known_lables.erase(state.bus.get_pc() - 1);
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
// bool myfunction(instr i, instr j) { return (i.pc < j.pc); }
void init(NESRom nes, std::string output)
{
    Header h = Header(nes.header);
    uint16_t pc_start = nes.prg_rom[0xfffd - 0x8000] << 8 | nes.prg_rom[0xfffc - 0x8000];
    uint16_t nmi = nes.prg_rom[0xfffb - 0x8000] << 8 | nes.prg_rom[0xfffa - 0x8000];

    Bus bus = Bus(nes.prg_rom, pc_start);
    bus.fill_instr(pc_start);
    std::map<uint16_t, std::string> known_lables;
    std::map<uint16_t, std::string> assembled;

    known_lables[pc_start] = "reset";
    known_lables[nmi] = "nmi";
    DisAsmState dis = {bus, known_lables, assembled, 0};
    auto prg = computer(dis);
    std::cout << h.disassm() << std::endl;
    std::ofstream outputFile(output);

    outputFile << h.disassm();
    outputFile << ".SEGMENT \"VECTORS\" \n";

    outputFile << ".addr reset \n";
    outputFile << ".addr nmi \n";

    outputFile << ".SEGMENT \"STARTUP\" \n";

    for (int i = 0; i < prg.size() - 1; i++)
    {
        for (int j = 0; j < prg.size() - i - 1; j++)
        {

            if (prg[j]->pc > prg[j + 1]->pc)

                std::swap(prg[j], prg[j + 1]);
        }
    }
    for (int i = 0; i < prg.size(); i++)
    {
        // printf("labe;l\n");
        if (dis.known_lables.find(prg[i]->pc) != dis.known_lables.end() //
            && dis.assembled.find(prg[i]->pc) == dis.assembled.end())
        {
            auto d = std::make_shared<Label>(dis.known_lables[prg[i]->pc], prg[i]->pc);
            dis.assembled.insert(std::make_pair(prg[i]->pc, dis.known_lables[prg[i]->pc - 1]));

            // dis.known_lables[]
            outputFile << d->disassm();
        }
        printf("0x %x \n", prg[i]->pc);

        outputFile << prg[i]->disassm();
    }
    for (const auto &[key, value] : dis.known_lables)
    {

        if (dis.assembled.find(key) == dis.assembled.end() && value != "")
        {
            auto d = std::make_shared<Label>(value, 0x00);
            outputFile << d->disassm();
        }
    }

    outputFile.close();
}