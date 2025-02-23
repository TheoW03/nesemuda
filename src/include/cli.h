#include <vector>
#include <iostream>

#ifndef OUT_H
#define OUT_H
struct Output
{
    std::string files;
    std::string output_files;
};

#endif
Output parse_cmd(std::vector<std::string> args);