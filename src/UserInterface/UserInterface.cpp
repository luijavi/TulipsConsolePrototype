#include "UserInterface.h"
#include <iostream>

UserInputType luis_ui::GetInput(InputParameters input_params)
{
    std::cout << input_params.prompt;
    if (input_params.read_on_new_line)
    {
        std::cout << "\n"
                  << "> ";
    }

    std::string user_response;
    std::getline(std::cin, user_response);

    switch (input_params.output_type)
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
