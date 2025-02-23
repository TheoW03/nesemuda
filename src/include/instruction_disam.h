#include <instruction.h>
#include <memory>

std::shared_ptr<instr> LDA(AddressMode addressMode, DisAsmState &disasm);
std::shared_ptr<instr> JMP(AddressMode addressMode, DisAsmState &disasm);
std::shared_ptr<instr> RTI(AddressMode addressMode, DisAsmState &disasm);