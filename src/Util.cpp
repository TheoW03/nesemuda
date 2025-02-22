#include <iostream>
#include <cstdio>

std::string byteToHex(uint8_t byte)
{
    char buffer[3];
    std::sprintf(buffer, "%02X", byte);
    return "$" + std::string(buffer);
}