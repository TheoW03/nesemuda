# NESEmuDASM 

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)



NESEmuDASM 

is a dynamic NES ROM disassembler with a ca65 target 
how it works is that instead of statically disassembling ROMs 

it simulates the execution flow of the PC by using a special type of emulator, an
emulator that does "fetch decode disassemble" as opposed to "fetch decode execute store". and with that  it can disassemble a ROM into source code that will
infact run on the machines hardware.  

## build instructions 

```sh 
cmake -S . -B build 
cmake --build build --config Release
./DisassmTetroid --help
```

