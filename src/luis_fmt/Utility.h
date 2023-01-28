#pragma once

#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include <limits>

namespace luis_fmt
{
	std::string to_cash(double amount);
	// Include file path in filename argument
	/*bool load_resource(const std::string& filename, char delimiter)
	{
		std::ifstream file{ filename, std::ios::in };

		if (!file.is_open())
		{
			std::cout << "Failed to open " << filename << std::endl;
			return false;
		}



		return false;
	}*/
}

namespace luis_math
{
	double round(double value, double precision = 1.0);

	// Prevent stack overflow - though given the nature of the game,
	// I may have to just ensure that the numeric type is increased
	// to hold bigger numbers.
	// Source: https://stackoverflow.com/a/3041689
	template<typename T>
	T add_without_overflow(const T& base_value, const T& adjustment_amount)
	{

		if ((base_value + adjustment_amount) < std::numeric_limits<T>::max())
		{
			return base_value + adjustment_amount;
		}
		else
		{
			// If the addition result results in overflow, then only return
			// the max numeric value
			return std::numeric_limits<T>::max());
		}
	}

	// Prevent stack underflow in subtraction operations
	template<typename T>
	T sub_without_underflow(const T& base_value, const T& adjustment_amount)
	{

		if ((base_value - adjustment_amount) > std::numeric_limits<T>::min())
		{
			return base_value - adjustment_amount;
		}
		else
		{
			// If the subtraction result results in underflow, then only return
			// the min numeric value
			return std::numeric_limits<T>::min());
		}
	}
}