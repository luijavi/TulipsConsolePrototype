#include "UserInterface.h"
#include <iostream>

std::variant<int, double, char, std::string> luis_ui::Read(std::string_view prompt, OutputType)
{
    return std::variant<int, double, char, std::string>();
}
