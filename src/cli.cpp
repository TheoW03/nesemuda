#include <vector>
#include <map>
#include <iostream>
#include <cli.h>
#include <functional>
#include <optional>
struct ParseFunction
{
    std::function<void(std::string &, Output &)> function;
    std::string help_text;
    int takes_args;
};
Output parse_cmd(std::vector<std::string> args)
{
    int state = 0;
    Output o;
    /* A function wrapper to a lambda function. */
    std::map<std::string,
             ParseFunction>
        option_handlers;
    std::string optop;
    std::map<char, std::string> short_hand;
    short_hand['c'] = "object-file";
    short_hand['o'] = "output-file";
    short_hand['v'] = "version";
    short_hand['h'] = "help";

    option_handlers["output-file"] = {[](std::string &value, Output &o)
                                      {
                                          o.output_files = value;
                                      },
                                      "output file", 1};

    option_handlers["help"] = {[&option_handlers](std::string &value, Output &o)
                               {
                                   std::cout << "TetroidDisasm v1.0.0" << std::endl;
                                   std::cout << "" << std::endl;
                                   std::cout << "   TetroidDisasm is a NESROm Disassembler." << std::endl;
                                   std::cout << "" << std::endl;
                                   std::cout << "usage: TetroidDisasm file [options]" << std::endl;
                                   std::cout << "" << std::endl;

                                   for (const auto &[key, value] : option_handlers)
                                   {
                                       std::cout << "   --" << key << ": " << value.help_text << std::endl; // Access the key
                                       std::cout << "" << std::endl;
                                   }
                               },
                               "cli documentation", 0};
    option_handlers["version"] = {[](std::string &value, Output &o)
                                  {
                                      std::cout << "1.0.0" << std::endl;
                                  },
                                  "prints version", 0};
    option_handlers["print-file"] = {[](std::string &value, Output &o)
                                     {
                                         o.print_file = true;
                                     },
                                     "print the output instead of storing it in .s file", 0};

    // func_c(2017);
    std::optional<ParseFunction> current;
    for (int i = 0; i < args.size(); i++)
    {
        if (!current.has_value() && args[i].size() < 2)
        {
            std::cout << "TetroidDisasm: arguement has to little characters to count as an option (they must be atleast 2 characters in length)" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (args[i].at(0) == '-' && args[i].at(1) != '-')
        {
            char short_optop = args[i].at(1);
            if (short_hand.find(short_optop) != short_hand.end())
            {
                current = option_handlers[short_hand[short_optop]];
                if (current.value().takes_args == 0)
                {
                    current.value().function(args[i], o);
                    current = {};
                }
            }
            else
            {
                std::cout << "TetroidDisasm: unknown option \"" << short_optop << "\" run -h or --help for a list of commands" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (args[i].at(0) == '-' && args[i].at(1) == '-')
        {
            optop = args[i].substr(2, args[i].size());
            if (option_handlers.find(optop) != option_handlers.end())
            {
                current = option_handlers[optop];
                if (current.value().takes_args == 0)
                {
                    current.value().function(args[i], o);
                    current = {};
                }
            }
            else
            {
                std::cout << "TetroidDisasm: unknown option \"" << optop << "\"run -h or --help for a list of commands" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (current.has_value())
        {
            current.value().function(args[i], o);
        }
        else
        {
            o.files = args[i];
        }
    }
    return o;
}
