# nesda 

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)


nesda 

is a CFG (control flow graph) aided NES ROM disassembler.

with a ca65 macro assembler target. 

It is way more accurate then your typical disassembler, Which takes any Assembled file 
and just converts each byte it sees to assembler without any thought.


## build instructions 

```sh 
cmake -S . -B build 
cmake --build build --config Release
./nesda --help
```

