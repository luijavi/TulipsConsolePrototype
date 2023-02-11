#include "Market.h"


#include <fstream>
#include <iostream>
#include <sstream>

Market::Market()
{
	InitFlowerMarket();
}

void Market::InitFlowerMarket()
{
	std::string filename{ "Resources\\FlowersList.txt" };
	std::ifstream flower_file{ filename, std::ios::in };

	if (!flower_file.is_open())
	{
		std::cout << "\nFailed to open " << filename << "!\n";
	}
	else
	{
		std::map<std::string, Flower> flower_map;
		static constexpr char delim = '|';
		static constexpr char sub_delim = '#';

		while (!flower_file.eof())
		{
			std::string line;
			std::getline(flower_file, line);

			if (line.empty() || line[0] == '$')
			{
				continue;
			}
			else
			{
				std::istringstream flower_data(line);

				Flower f(flower_data);
				
				flower_map.emplace(f);

			}
			
		}
		
	}
	
}
