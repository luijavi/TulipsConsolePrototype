#include "Utility.h"

namespace luis_fmt
{
	std::string to_cash(double amount)
	{
		amount *= 100;

		std::ostringstream oss;
		oss.imbue(std::locale("en_US.UTF-8"));
		oss << std::showbase << std::put_money(amount);

		return oss.str();
	}
}

namespace luis_math
{
	double round(double value, double precision)
	{
		return std::round(value / precision) * precision;
	}
}

int luis_utility::count_character(std::string_view source_string, char character_to_count)
{
	int count = 0;

	for (auto s : source_string)
	{
		if (s == character_to_count)
		{
			++count;
		}
	}

	return count;
}
