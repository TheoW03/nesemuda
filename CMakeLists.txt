cmake_minimum_required(VERSION 3.10)

project(MyProject)
set(EXECUTABLE_NAME nesemuda)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(${EXECUTABLE_NAME} PRIVATE src/include/)

add_executable(${EXECUTABLE_NAME}
                src/main.cpp
                src/Load_Rom.cpp
                src/instruction_disassemble.cpp
                src/Disassemble_emulator.cpp
                src/Util.cpp
                src/instruction_map.cpp
                src/instr_bus.cpp
                src/instructions.cpp
                src/cli.cpp)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/..)
