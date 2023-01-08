#include "UserInterface.h"
#include <iostream>

std::variant<int, double, char, std::string> luis_ui::GetInput(std::string_view prompt, OutputType output_type, bool newline_input)
{
    std::cout << prompt;
    if (newline_input)
    {
        std::cout << "\n"
                  << "> ";
    }

    std::string user_response;
    std::getline(std::cin, user_response);

    switch (output_type)
    {
        case OutputType::kInt:
        {

        } break;

        case OutputType::kReal:
        {

        } break;

        case OutputType::kChar:
        {

        } break;

        case OutputType::kString:
        {

        } break;

    }
}
