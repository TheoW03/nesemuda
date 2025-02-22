
#include <memory>
#include <instruction.h>

std::vector<uint8_t> diasm_addressmode(AddressMode addressMode, DisAsmState &disasm)
{
    std::vector<uint8_t> ret;

    if (addressMode == AddressMode::IMMEDIATE)
    {
        ret.push_back(disasm.bus.get_instr());
        return ret;
    }
}
std::shared_ptr<instr> LDA(AddressMode addressMode, DisAsmState &disasm)
{
    std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm);
    return std::make_shared<Lda>(addressMode, data_vec);
}
