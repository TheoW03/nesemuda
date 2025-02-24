# Tetroid Dis Assembler 

Tetroid Disassembler 

is a dynamic NES ROM disassembler with a ca65 target 
how it works is that instead of statically disassembling ROMs 
it simulates the execution flow of the PC. and uses that to 
accurately disassemble your ROM with very easily.

## build instructions 

```sh 
cmake -S . -B build 
cmake --build build --config Release
./DisassmTetroid --help
```

