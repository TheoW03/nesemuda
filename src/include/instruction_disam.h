#include <instruction.h>
#include <memory>

std::shared_ptr<instr> LDA(AddressMode addressMode, DisAsmState &disasm);