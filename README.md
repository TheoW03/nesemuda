# TetroidNESDisAssembler 

TetroidNESDisAssembler 

is a dynamic NES ROM disassembler with a ca65 target 
how it works is that instead of statically disassembling ROMs 

it simulates the execution flow of the PC by using a special type of emulator. and with that 
it can disassemble a ROM more accurately then your typical static disassembler

## build instructions 

```sh 
cmake -S . -B build 
cmake --build build --config Release
./DisassmTetroid --help
```

