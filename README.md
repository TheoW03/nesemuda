# nesda 

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

CFG (control flow graph) aided NES ROM disassembler.

with a ca65 macro assembler target. 

It is way more accurate then your typical disassembler, Which takes any Assembled file 
and just converts each byte it sees to assembler without any thought.

what it does instead is it disassembles. but looks for instructions where the PC will be changed such as
JMP, RTI, RTS when it apporahces these instructions it looks for the next address that needs to be disassembled. 

RTI and RTS read directly from a queue that gets populated at branches. however, JMP first attempts to JMP to the address next to jmp if that address is already disassembled. It goes through the queue.
if we run out of addresses is when disassembly is over.

and the next stage we do is sort the instructions based on PC.

## build instructions 

```sh 
cmake -S . -B build 
cmake --build build --config Release
./nesda --help
```

