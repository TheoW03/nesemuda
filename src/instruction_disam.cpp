
#include <memory>
#include <instruction.h>

std::shared_ptr<instr> LDA(AddressMode addressMode, DisAsmState &disasm)
{
    uint8_t data = disasm.bus.get_instr();
    std::vector<uint8_t> data_vec;
    data_vec.push_back(data);
    return std::make_shared<Lda>(addressMode, data_vec);
}
