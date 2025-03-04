#include <memory>
#include <instruction.h>
#include <instruction_map.h>
#define NES_START 0x8000 // this is the smallest a NES ROM can be
Bus::Bus(std::vector<uint8_t> instr, uint16_t pc_starting)
{
    this->instr = instr;
    this->reset_vector = pc_starting;
}

// old concept from my NES emulator
//  what this is it queues the next bytes the PC will look at

void Bus::fill_instr(uint16_t new_pc)
{

    this->pc = new_pc;
    stored_instructions[0] = instr[(pc + 1) - reset_vector];
    stored_instructions[1] = instr[(pc - reset_vector)];
    pc_visited.insert(pc);
    pc++;
}
uint8_t Bus::get_instr()
{

    uint8_t current_instruction = stored_instructions[1];
    stored_instructions[1] = stored_instructions[0];
    stored_instructions[0] = instr[(this->pc + 1) - NES_START];
    pc_visited.insert(pc);
    // printf("%x \n", instr[0xfffa - reset_vector]);
    pc++;

    return current_instruction;
}

uint16_t Bus::read_rom_mem(uint16_t mem_address)
{
    uint8_t byte1 = instr[(mem_address + 1) - NES_START];
    uint8_t byte2 = instr[mem_address - NES_START];
    return byte1 << 8 | byte2;
}

uint16_t Bus::get_pc()
{
    return this->pc;
}
void Bus::add_to_queue(uint16_t addr)
{
    // at a branch instr
    // what we will do is push the new PC into this queue
    // once we run out instructions or apporach RTS, or RTI
    // we will set the PC to a value in this queue
    // effectivelya allowing us to disassemble the branch
    uint16_t new_pc = addr;
    // printf("pc adding to quue: 0x%x instr at the addr: 0x%x \n", new_pc, instr[new_pc - reset_vector]);
    // printf("%d \n", InstructionValid(instr[new_pc - reset_vector]));
    if (pc_visited.find(new_pc) == pc_visited.end())
    {
        pc_queue.push_back(addr);
    }
}
uint16_t Bus::get_next_queue()
{
    if (pc_queue.size() == 0)
    {
        return 0;
    }

    uint16_t new_pc = pc_queue[0];

    // printf("%x %d \n", new_pc, pc_visited.find(new_pc) != pc_visited.end());
    // printf("%x \n", pc);
    pc_queue.erase(pc_queue.begin());
    // a bit hacky but if its in the range of being the PC it will constitute it as the PC
    if ((new_pc + 1) == pc || new_pc == pc)
    {
        return new_pc;
    }
    if (pc_visited.find(new_pc) != pc_visited.end())
    {
        return get_next_queue();
    }

    return new_pc;
}