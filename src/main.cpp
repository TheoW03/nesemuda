#include <iostream>
#include <RomUtil.h>

int main(int argc, char const *argv[])
{
    /* code */
    auto c = file_tobyte_vector("./games/TestRom1.nes");
    printf("%c %c %c %c \n", c[0], c[1], c[2], c[3]);

    // auto b =

    return 0;
}
