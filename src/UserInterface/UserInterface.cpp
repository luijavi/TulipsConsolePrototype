#include "UserInterface.h"
#include <iostream>
#include <algorithm>

bool ValidateResponse(const InputParameters& input_params, std::string user_response)
{
    bool is_response_valid = false;
    switch (input_params.output_type)
    {
        case OutputType::kInt:
        {
            is_response_valid = std::stoi(user_response) >= input_params.min_value.value().index()
                && std::stoi(user_response) <= input_params.max_value.value().index();
        } break;

        case OutputType::kReal:
        {
            is_response_valid = std::stod(user_response) >= input_params.min_value.value().index()
                && std::stod(user_response) <= input_params.max_value.value().index();
        } break;

        // For characters responses, we want to make sure the player only entered 1 character. If more
        // that 1 character was entered, then we immediately break with an invalid entry. However,
        // even if 1 character was entered, we need to make sure that it's a valid response against
        // the list of valid responses provided by user.
        // TODO: May have to check for special characters
        case OutputType::kChar:
        {
            if (user_response.empty() || user_response.length() > 1)
            {
                break;
            }
        }

        case OutputType::kString:
        {
            if (user_response.empty())
            {
                break;
            }


            is_response_valid = 
                std::find(input_params.valid_responses->begin(), input_params.valid_responses->end(), user_response)
                != input_params.valid_responses->end();
        } break;
    }

    return is_response_valid;
}

void PromptUser(std::string prompt, bool new_line_input)
{
    std::cout << prompt;
    if (new_line_input)
    {
        std::cout << "\n"
            << "> ";
    }
}

UserInputType luis_ui::GetInput(const InputParameters& input_params)
{
    PromptUser(input_params.prompt, input_params.new_line_input);

    std::string user_response;
    std::getline(std::cin, user_response);

    // Validate user input
    if (input_params.validate_input)
    {
        std::string error_message = input_params.invalid_input_message;
        // If user did not provide an error message, then use a default one.
        if (error_message.empty())
        {
            error_message = "Invalid entry!";
        }

        while (!ValidateResponse(input_params, user_response))
        {
            std::cout << "\n" << error_message << "\n";
            PromptUser(input_params.prompt, input_params.new_line_input);
            user_response.clear();
            std::getline(std::cin, user_response);
        }
    }
    

    switch (input_params.output_type)
    {
        case OutputType::kInt:
        {
            return std::stoi(user_response);
        } break;

        case OutputType::kReal:
        {
            return std::stod(user_response);
        } break;

        case OutputType::kChar:
        {
            return user_response[0];
        } break;

        case OutputType::kString:
        {
            return user_response;
        } break;
    }
}
