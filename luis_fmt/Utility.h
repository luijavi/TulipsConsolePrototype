#pragma once

#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>

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
}