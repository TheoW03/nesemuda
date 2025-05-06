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
    // for (int val : pc_visited)
    // {
    //     printf("%x \n", val);
    //     // std::cout << val << std::endl;
    // }
    // for(int i -)
    // while (!work_list.empty())
    // {
    //     work_list.pop();
    //     /* code */
    // }

    this->pc = new_pc;
    // pc_visited.insert(new_pc);
    // work_list.push(new_pc);
    stored_instructions[1] = instr[(pc - reset_vector)];
    stored_instructions[0] = instr[(pc + 1) - reset_vector];
    pc++;
}

uint8_t Bus::get_instr(bool checkifdisassembled)
{
    if (checkifdisassembled && this->pc_visited.find(pc - 1) != this->pc_visited.end())
    {
        return 0;
    }
    uint16_t current_pc = pc;
    pc_visited.insert(current_pc - 1);
    uint8_t current_instruction = stored_instructions[1];
    stored_instructions[1] = stored_instructions[0];
    stored_instructions[0] = instr[(this->pc + 1) - reset_vector];
    // work_list.push(pc);
    // printf("visted oc %x \n", pc);
    // printf("current instr %x \n", current_instruction);
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
    // printf("pc adding to quue: 0x%x instr at the addr: 0x%x 0x%x \n", new_pc, this->get_pc(), this->instr[(this->get_pc() - 1) - 0x8000]);
    // printf("%d \n", InstructionValid(instr[new_pc - reset_vector]));
    if (pc_visited.find(new_pc) == pc_visited.end())
    {
        // printf("added: %x\n", new_pc);
        pc_queue.push_back(addr);
    }
    // else
    // {
    //     printf("failed to add: %x\n", new_pc);
    // }
}
uint16_t Bus::get_next_queue()
{
    if (pc_queue.size() == 0)
    {
        return 0;
    }

    uint16_t new_pc = pc_queue[0];
    // printf("pc == %x \n", new_pc);

    // printf("%x %d \n", new_pc, (pc_visited.find(new_pc) != pc_visited.end()));
    // printf("%x \n", pc);
    // printf("%x \n", this->instr[(this->pc - 0x8000) - 1]);
    pc_queue.erase(pc_queue.begin());
    // printf("%d \n", pc_queue.size());
    // for (int i = 0; i < pc_queue.size(); i++)
    // {
    //     printf("pc quee: %x \n", pc_queue[i]);
    // }
    // if (new_pc == pc && new_pc == (pc + 1))
    // {
    //     return new_pc;
    // }
    if (pc_visited.find(new_pc) != pc_visited.end())
    {
        // printf("pc %x  is already visted \n", new_pc);
        return get_next_queue();
    }

    return new_pc;
}