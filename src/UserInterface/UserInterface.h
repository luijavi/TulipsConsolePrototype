#pragma once
#include <variant>
#include <string>

//enum class PromptType
//{
//	kYesOrNo,
//	kMultipleChoice,
//	kNumeric,
//	kAlphaNumeric
//};
//

typedef std::variant<int, double, char, std::string> UserInputType;

enum class OutputType
{
	kInt,
	kReal,
	kChar,
	kString
};

struct InputParameters
{
	OutputType output_type = OutputType::kString;
	std::string prompt;
	bool read_on_new_line = false;

};

namespace luis_ui
{
	// TODO: Does the order of types in variant matter?
	UserInputType GetInput(InputParameters input_params);
}