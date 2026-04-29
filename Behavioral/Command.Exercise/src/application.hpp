#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <algorithm>
#include <unordered_map>

#include "command.hpp"
#include "console.hpp"

namespace Messages
{
    constexpr auto msg_unknown_cmd = "Unknown command: ";
    constexpr auto msg_prompt = "Enter a command: ";
};

class Application
{
    static const std::string cmd_exit;

    Console& console_;
    std::unordered_map<std::string, CommandSharedPtr> cmds_;

public:
    Application(Console& console)
        : console_{console}
    {
    }

    void run()
    {
        while (true)
        {
            console_.print(Messages::msg_prompt);

            auto cmd = console_.get_line();
            to_upper(cmd);

            if (cmd == Commands::cmd_exit)
                break;

            if (auto pos = cmds_.find(cmd); pos != cmds_.end())
            {
                pos->second->execute();
            }
            else
            {
                console_.print(Messages::msg_unknown_cmd + cmd);
            }
        }
    }

    void add_command(std::string name, CommandSharedPtr cmd)
    {
        to_upper(name);
        cmds_.emplace(std::move(name), cmd);
    }
public:
    void to_upper(std::string& text)
    {
        std::transform(text.begin(), text.end(), text.begin(), [](auto c) { return std::toupper(c);});
    }
};

#endif // APPLICATION_HPP
