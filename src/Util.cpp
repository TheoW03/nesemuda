#include <iostream>
#include <cstdio>

std::string byteToHex8(uint8_t byte)
{
    char buffer[3];
    std::sprintf(buffer, "%02X", byte);
    return "$" + std::string(buffer);
}
std::string byteToHex16(uint16_t byte)
{
    char buffer[5];
    std::sprintf(buffer, "%02X", byte);
    return "$" + std::string(buffer);
}