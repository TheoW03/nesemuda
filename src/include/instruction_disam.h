#include <instruction.h>
#include <memory>

std::shared_ptr<instr> LDA(AddressMode addressMode, DisAsmState &disasm);
std::shared_ptr<instr> LDY(AddressMode addressMode, DisAsmState &disasm);
std::shared_ptr<instr> LDX(AddressMode addressMode, DisAsmState &disasm);

std::shared_ptr<instr> JMP(AddressMode addressMode, DisAsmState &disasm);
std::shared_ptr<instr> RTI(AddressMode addressMode, DisAsmState &disasm);

std::shared_ptr<instr> BEQ(AddressMode addressMode, DisAsmState &disasm);
std::shared_ptr<instr> BNE(AddressMode addressMode, DisAsmState &disasm);
std::shared_ptr<instr> BCC(AddressMode addressMode, DisAsmState &disasm);
std::shared_ptr<instr> BCS(AddressMode addressMode, DisAsmState &disasm);
std::shared_ptr<instr> BPL(AddressMode addressMode, DisAsmState &disasm);
std::shared_ptr<instr> BMI(AddressMode addressMode, DisAsmState &disasm);
