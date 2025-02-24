
#include <memory>
#include <instruction.h>

std::vector<uint8_t> diasm_addressmode(AddressMode addressMode, DisAsmState &disasm)
{
    std::vector<uint8_t> ret;

    if (addressMode == AddressMode::IMMEDIATE      //
        || addressMode == AddressMode::ZERO_PAGE   //
        || addressMode == AddressMode::ZERO_PAGE_X //
        || addressMode == AddressMode::ZERO_PAGE_Y //
        || addressMode == AddressMode::INDIRECT_X  //
        || addressMode == AddressMode::INDIRECT_Y  //

    )
    {
        ret.push_back(disasm.bus.get_instr());
        return ret;
    }
    else if (addressMode == AddressMode::ABSOLUTE || addressMode == AddressMode::ABSOLUTE_X || addressMode == AddressMode::ABSOLUTE_Y)
    {
        ret.push_back(disasm.bus.get_instr());
        ret.push_back(disasm.bus.get_instr());
        return ret;
    }
}
std::shared_ptr<instr> LDA(AddressMode addressMode, DisAsmState &disasm)
{
    auto pc = disasm.bus.get_pc() - 1;
    std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm);
    return std::make_shared<Lda>(addressMode, data_vec, pc);
}
std::shared_ptr<instr> JMP(AddressMode addressMode, DisAsmState &disasm)
{
    auto pc = disasm.bus.get_pc() - 1;
    std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm);
    if (addressMode == AddressMode::ABSOLUTE)
    {
        uint16_t a = data_vec[1] << 8 | data_vec[0];

        if (disasm.known_lables.find(a + 1) == disasm.known_lables.end())
        {
            disasm.known_lables.insert(std::make_pair(a + 1, "L" + std::to_string(disasm.label++)));
        }
        disasm.bus.fill_instr(a);
        return std::make_shared<Jmp>(addressMode, disasm.known_lables[a + 1], pc);
    }

    return std::make_shared<Jmp>(addressMode, data_vec, pc);
    // disasm.lables.insert();
}
std::shared_ptr<instr> RTI(AddressMode addressMode, DisAsmState &disasm)
{
    auto pc = disasm.bus.get_pc() - 1;

    return std::make_shared<Rti>(addressMode, pc);
}
