
#include <memory>
#include <instruction.h>
#include "instruction_disam.h"

// InstrData diasm_addressmode()
std::string handle_labels(DisAsmState &disasm, uint16_t label_pc)
{
    if (disasm.known_lables.find(label_pc) == disasm.known_lables.end())
    {
        disasm.known_lables.insert(std::make_pair(label_pc, "L" + std::to_string(disasm.label++)));
    }
    return disasm.known_lables[label_pc];
}
InstrData diasm_addressmode(AddressMode addressMode, DisAsmState &disasm)
{
    InstrData ret;
    // std::vector<uint8_t> ret;

    if (addressMode == AddressMode::IMMEDIATE      //
        || addressMode == AddressMode::ZERO_PAGE   //
        || addressMode == AddressMode::ZERO_PAGE_X //
        || addressMode == AddressMode::ZERO_PAGE_Y //
        || addressMode == AddressMode::INDIRECT_X  //
        || addressMode == AddressMode::INDIRECT_Y  //
        || addressMode == AddressMode::RELATIVE

    )
    {
        ret.instr_data.push_back(disasm.bus.get_instr(false).value());
        ret.label = {};
    }
    else if (addressMode == AddressMode::ABSOLUTE || addressMode == AddressMode::ABSOLUTE_X || addressMode == AddressMode::ABSOLUTE_Y)
    {

        uint8_t lower_half = disasm.bus.get_instr(false).value();
        uint8_t upper_half = disasm.bus.get_instr(false).value();
        uint16_t pc = upper_half << 8 | lower_half;
        ret.instr_data.push_back(lower_half);
        ret.instr_data.push_back(upper_half);

        if (pc >= 0x8000)
        {
            ret.label = handle_labels(disasm, pc);
        }
    }
    return ret;
    // else if (addressMode == AddressMode::ABSOLUTE || addressMode == AddressMode::ABSOLUTE_X || addressMode == AddressMode::ABSOLUTE_Y)
    // {
    //     ret.push_back(disasm.bus.get_instr());
    //     ret.push_back(disasm.bus.get_instr());
    // }
    // return ret;
}

std::string handle_branch(DisAsmState &disasm, int8_t new_branch)
{
    uint16_t branched_pc = (disasm.bus.get_pc() + new_branch) - 1;
    std::string label = handle_labels(disasm, branched_pc);
    disasm.bus.add_to_queue(branched_pc);
    return label;
}

void HandleJMP(DisAsmState &disasm)
{
    // disasm.bus.pc_visited.erase(disasm.bus.get_pc());
    // disasm.bus.pc_visited.erase(disasm.bus.get_pc() - 1);

    auto c = disasm.bus.get_next_queue();
    if (c.has_value())
    {
        disasm.bus.fill_instr(c.value());
    }
    else
    {
        disasm.is_finished = true;
    }
    // printf("new_jmppc: %x \n", c);
    // printf("current_pc: %x \n", disasm.bus.get_pc());
    // printf("%x \n", disasm.bus.instr[c - 0x8000]);
}

/*
for LDA, LDY, ADC, LDX...
 */
std::shared_ptr<instr> disassemble_MultiByteInstr(AddressMode addressMode, DisAsmState &disasm, std::string name)
{
    auto pc = disasm.bus.get_pc() - 1;
    auto data_vec = diasm_addressmode(addressMode, disasm);
    return std::make_shared<MultiByteInstr>(name, addressMode, data_vec, pc);
}

std::shared_ptr<instr> disassemble_Branch(AddressMode addressMode, DisAsmState &disasm, std::string name)
{
    auto pc = disasm.bus.get_pc() - 1;
    std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm).instr_data;
    int8_t new_branch = (int8_t)data_vec[0];
    auto label = handle_branch(disasm, new_branch);
    return std::make_shared<BranchInstr>(name, label, pc);
}

std::shared_ptr<instr> disassemble_Onebyte(AddressMode addressMode, DisAsmState &disasm, std::string name)
{
    auto pc = disasm.bus.get_pc() - 1;

    return std::make_shared<oneByteInstr>(name, pc);
}

std::shared_ptr<instr> disassemble_RtsRti(AddressMode addressMode, DisAsmState &disasm, std::string name)
{
    auto pc = disasm.bus.get_pc() - 1;
    HandleJMP(disasm);
    return std::make_shared<oneByteInstr>(name, pc);
}

std::shared_ptr<instr> disassemble_brk(AddressMode addressMode, DisAsmState &disasm, std::string name)
{
    auto pc = disasm.bus.get_pc() - 1;
    HandleJMP(disasm);
    return std::make_shared<oneByteInstr>(name, pc);
}

// TODO
//  what Jump should do instead of pushing the address into the queue
//  to be disassembled later. jump to the address, if the address is already disassembled
// goto an address in the queue

// if JMP INDIRECT. if the address is in the rom we will jump to its contents
//  if not work our way down the queue

std::shared_ptr<instr> JMP(AddressMode addressMode, DisAsmState &disasm, std::string name)
{
    auto pc = disasm.bus.get_pc() - 1;
    // std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm);
    auto data = diasm_addressmode(addressMode, disasm);
    if (addressMode == AddressMode::ABSOLUTE)
    {

        uint16_t jmp_pc = data.instr_data[1] << 8 | data.instr_data[0];
        // std::string label = handle_labels(disasm, jmp_pc);
        disasm.bus.pc_visited.erase(disasm.bus.get_pc());
        disasm.bus.pc_visited.erase(disasm.bus.get_pc() - 1);
        // disasm.bus.pc_visited.erase(disasm.bus.get_pc() - 2);

        disasm.bus.add_to_queue(jmp_pc);
        HandleJMP(disasm);
        // printf("jmp pc:%x \n", jmp_pc + 1);
        // printf("jmp pc:%x \n", jmp_pc + 1);
    }
    return std::make_shared<Jmp>(addressMode, data, pc);
}
std::shared_ptr<instr> JSR(AddressMode addressMode, DisAsmState &disasm, std::string name)
{
    // printf("jsr \n");
    auto pc = disasm.bus.get_pc() - 1;
    // printf("retriving data \n");
    // printf("retriving data %x \n", pc);

    auto data = diasm_addressmode(addressMode, disasm);
    uint16_t jmp_pc = data.instr_data[1] << 8 | data.instr_data[0];
    // std::string label = handle_labels(disasm, jmp_pc);
    // disasm.bus.add_to_queue(disasm.bus.get_pc() - 1);
    // printf("added to queue \n");

    disasm.bus.add_to_queue(jmp_pc);
    // printf("jsr pc instr: %x \n", disasm.bus.instr[(disasm.bus.get_pc()) - 0x8000]);

    // printf("current_pc %x \n", disasm.bus.get_pc() - 1);

    // auto new_pc = disasm.bus.get_next_queue();
    // disasm.bus.fill_instr(new_pc);
    return std::make_shared<Jsr>(addressMode, data, pc);
}

// std::shared_ptr<instr> LDA(AddressMode addressMode, DisAsmState &disasm)
// {
//     auto pc = disasm.bus.get_pc() - 1;
//     auto data_vec = diasm_addressmode(addressMode, disasm);
//     return std::make_shared<MultiByteInstr>("lda", addressMode, data_vec, pc);
// }

// std::shared_ptr<instr> LDY(AddressMode addressMode, DisAsmState &disasm)
// {

//     auto pc = disasm.bus.get_pc() - 1;
//     auto data_vec = diasm_addressmode(addressMode, disasm);
//     return std::make_shared<MultiByteInstr>("ldy", addressMode, data_vec, pc);
// }

// std::shared_ptr<instr> LDX(AddressMode addressMode, DisAsmState &disasm)
// {

//     auto pc = disasm.bus.get_pc() - 1;
//     auto data_vec = diasm_addressmode(addressMode, disasm);
//     return std::make_shared<MultiByteInstr>("ldx", addressMode, data_vec, pc);
// }

// std::shared_ptr<instr> RTI(AddressMode addressMode, DisAsmState &disasm)
// {

//     auto pc = disasm.bus.get_pc() - 1;
//     // printf("rti: %x \n", pc);

//     HandleJMP(disasm);
//     // uint16_t c = disasm.bus.get_next_queue();
//     // printf("%x \n", c);
//     // if (c != 0)
//     //     disasm.bus.fill_instr(c);

//     return std::make_shared<oneByteInstr>("rti", pc);
// }
// std::shared_ptr<instr> RTS(AddressMode addressMode, DisAsmState &disasm)
// {

//     auto pc = disasm.bus.get_pc() - 1;
//     HandleJMP(disasm);

//     return std::make_shared<oneByteInstr>("rts", pc);
// }

// std::shared_ptr<instr> BEQ(AddressMode addressMode, DisAsmState &disasm)
// {
//     auto pc = disasm.bus.get_pc() - 1;
//     std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm).instr_data;
//     int8_t new_branch = (int8_t)data_vec[0];
//     auto label = handle_branch(disasm, new_branch);
//     return std::make_shared<BranchInstr>("beq", label, pc);
// }

// std::shared_ptr<instr> BNE(AddressMode addressMode, DisAsmState &disasm)
// {

//     auto pc = disasm.bus.get_pc() - 1;
//     std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm).instr_data;
//     int8_t new_branch = (int8_t)data_vec[0];
//     auto label = handle_branch(disasm, new_branch);
//     return std::make_shared<BranchInstr>("bne", label, pc);
// }

// std::shared_ptr<instr> BCC(AddressMode addressMode, DisAsmState &disasm)
// {

//     auto pc = disasm.bus.get_pc() - 1;
//     std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm).instr_data;
//     int8_t new_branch = (int8_t)data_vec[0];
//     auto label = handle_branch(disasm, new_branch);
//     return std::make_shared<BranchInstr>("bcc", label, pc);
// }

// std::shared_ptr<instr> BCS(AddressMode addressMode, DisAsmState &disasm)
// {

//     auto pc = disasm.bus.get_pc() - 1;
//     std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm).instr_data;
//     int8_t new_branch = (int8_t)data_vec[0];
//     auto label = handle_branch(disasm, new_branch);
//     return std::make_shared<BranchInstr>("bcs", label, pc);
// }

// std::shared_ptr<instr> BPL(AddressMode addressMode, DisAsmState &disasm)
// {

//     auto pc = disasm.bus.get_pc() - 1;
//     std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm).instr_data;
//     int8_t new_branch = (int8_t)data_vec[0];
//     auto label = handle_branch(disasm, new_branch);
//     return std::make_shared<BranchInstr>("bpl", label, pc);
// }

// std::shared_ptr<instr> BMI(AddressMode addressMode, DisAsmState &disasm)
// {

//     auto pc = disasm.bus.get_pc() - 1;
//     std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm).instr_data;
//     int8_t new_branch = (int8_t)data_vec[0];
//     auto label = handle_branch(disasm, new_branch);
//     return std::make_shared<BranchInstr>("bmi", label, pc);
// }

// std::shared_ptr<instr> CLC(AddressMode addressMode, DisAsmState &disasm)
// {
//     auto pc = disasm.bus.get_pc() - 1;
//     return std::make_shared<oneByteInstr>("clc", pc);
// }

// std::shared_ptr<instr> SEC(AddressMode addressMode, DisAsmState &disasm)
// {
//     auto pc = disasm.bus.get_pc() - 1;
//     return std::make_shared<oneByteInstr>("sec", pc);
// }

// std::shared_ptr<instr> CLD(AddressMode addressMode, DisAsmState &disasm)
// {
//     auto pc = disasm.bus.get_pc() - 1;
//     return std::make_shared<oneByteInstr>("cld", pc);
// }

// std::shared_ptr<instr> SED(AddressMode addressMode, DisAsmState &disasm)
// {
//     auto pc = disasm.bus.get_pc() - 1;
//     return std::make_shared<oneByteInstr>("sed", pc);
// }

// std::shared_ptr<instr> CLI(AddressMode addressMode, DisAsmState &disasm)
// {
//     auto pc = disasm.bus.get_pc() - 1;
//     return std::make_shared<oneByteInstr>("cli", pc);
// }

// std::shared_ptr<instr> CLV(AddressMode addressMode, DisAsmState &disasm)
// {
//     auto pc = disasm.bus.get_pc() - 1;
//     return std::make_shared<oneByteInstr>("clv", pc);
// }

// std::shared_ptr<instr> INC(AddressMode addressMode, DisAsmState &disasm)
// {
//     return std::shared_ptr<instr>();
// }

// std::shared_ptr<instr> INX(AddressMode addressMode, DisAsmState &disasm)
// {

//     auto pc = disasm.bus.get_pc() - 1;
//     return std::make_shared<oneByteInstr>("inx", pc);
// }

// std::shared_ptr<instr> INY(AddressMode addressMode, DisAsmState &disasm)
// {
//     auto pc = disasm.bus.get_pc() - 1;
//     return std::make_shared<oneByteInstr>("iny", pc);
// }

// std::shared_ptr<instr> BVC(AddressMode addressMode, DisAsmState &disasm)
// {
//     auto pc = disasm.bus.get_pc() - 1;
//     std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm).instr_data;
//     int8_t new_branch = (int8_t)data_vec[0];
//     auto label = handle_branch(disasm, new_branch);
//     return std::make_shared<BranchInstr>("bvc", label, pc);
// }

// std::shared_ptr<instr> BVS(AddressMode addressMode, DisAsmState &disasm)
// {
//     auto pc = disasm.bus.get_pc() - 1;
//     std::vector<uint8_t> data_vec = diasm_addressmode(addressMode, disasm).instr_data;
//     int8_t new_branch = (int8_t)data_vec[0];
//     auto label = handle_branch(disasm, new_branch);
//     return std::make_shared<BranchInstr>("bvs", label, pc);
// }

// std::shared_ptr<instr> SEI(AddressMode addressMode, DisAsmState &disasm)
// {
//     auto pc = disasm.bus.get_pc() - 1;
//     return std::make_shared<oneByteInstr>("sei", pc);
// }
