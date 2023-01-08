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

namespace luis_ui
{
	enum class OutputType
	{
		kInt,
		kReal,
		kChar,
		kString
	};

	// TODO: Does the order of types in variant matter?
	std::variant<int, double, char, std::string> 
		GetInput(std::string_view prompt, OutputType output_type = OutputType::kString, bool newline_input = false);
}