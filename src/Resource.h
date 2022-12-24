#pragma once
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <istream>

// TODO: This is still not ideal, I guess. Maybe rename "Resource.h" to something that makes more sense?
template<typename MapType>
bool LoadAndParse(const std::string& filename, std::map<std::string, MapType>& destination)
{
	std::string full_filepath = "Resources\\" + filename;
	std::ifstream file{ full_filepath, std::ios::in };

	if (!file.is_open())
	{
		std::cerr << "\nFailed to open " << full_filepath << std::endl;
		return false;
	}
	else
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);

			if (line[0] == '$' || line.empty())
			{
				continue;
			}
			else
			{
				std::istringstream data(line);
				std::string key;
				std::getline(data, key, '|');
				destination.insert(key, MapType(data));
			}
		}
		return true;
	}
	return true;
}