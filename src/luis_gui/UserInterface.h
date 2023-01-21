#pragma once
#include <variant>
#include <string>
#include <vector>
#include <optional>

namespace luis_gui
{
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
		bool new_line_input = false;
		bool validate_input = true;
		std::string prompt;
		std::string invalid_input_message;
		std::optional<std::vector<UserInputType>> valid_responses;
		std::optional<std::variant<std::monostate, double, int>> min_value;
		std::optional<std::variant<std::monostate, double, int>> max_value;
	};

	UserInputType GetInput(const InputParameters& input_params);
}