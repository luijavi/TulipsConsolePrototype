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
		kDouble,
		kChar,
		kString
	};

	// TODO: Does the order 
	std::variant<int, double, char, std::string> Read(std::string_view prompt, OutputType = OutputType::kString);
}