#include "Market.h"

#include <tuple>
#include <fstream>
#include <iostream>

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
		std::map<std::string, FlowerMarketData> flower_map;
	}
	
}
