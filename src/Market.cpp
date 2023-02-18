#include "Market.h"
#include "Flower.h"
#include "City.h"
#include "luis_utility/Utility.h"


#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Market::Market(std::mt19937_64& random_engine)
	:
	m_engine(random_engine)
{
	InitFlowerMarket();
}

//TODO: Might have to also pass the random_device to this function
void Market::Update()
{
	for (auto& city_map : m_flower_market)
	{
		for (auto& flower_map : city_map.second)
		{
			Flower& f = flower_map.second;

			auto min_quantity = m_rarity_map.find(f.GetRarity())->second.min_quantity;
			auto max_quantity = m_rarity_map.find(f.GetRarity())->second.max_quantity;
			auto min_price = m_rarity_map.find(f.GetRarity())->second.min_price;
			auto max_price = m_rarity_map.find(f.GetRarity())->second.max_price;
			std::uniform_int_distribution<int> quantity_range(min_quantity, max_quantity);
			std::uniform_real_distribution<double> price_range(min_price, max_price);

			int quantity = quantity_range(m_engine);
			f.SetQuantity(quantity);

			double buy_price = luis_math::round(price_range(m_engine), 0.01);
			f.SetBuyPrice(buy_price);
		}
	}
}

void Market::InitFlowerMarket()
{
	std::string flower_filename{ "Resources\\FlowersList.txt" };
	std::ifstream flower_file{ flower_filename, std::ios::in };

	static constexpr char delim = '|';
	static constexpr char sub_delim = '#';
	
	std::map<std::string, Flower> flower_map;

	if (!flower_file.is_open())
	{
		std::cout << "\nFailed to open " << flower_filename << "!\n";
	}
	else
	{

		std::string header;
		std::getline(flower_file, header);

		while (!flower_file.eof())
		{
			std::string line;
			std::getline(flower_file, line);

			std::istringstream flower_data(line);

			Flower f(flower_data);
			
			flower_map.emplace(f.GetName(), f);
		}

		flower_file.close();
		
	}

	std::string cities_filename{ "Resources\\CitiesList.txt" };
	std::ifstream cities_file{ cities_filename, std::ios::in };

	if (!cities_file.is_open())
	{
		std::cout << "\nFailed to open " << cities_filename << "!\n";
	}
	else
	{
		std::string header;
		std::getline(cities_file, header);

		// This is actually the number of columns - 1, since it's based on the number
		// of times the '|' occurs in the header line, which only shows up between
		// columns. So if the header is like: $col1|col2|col3, the num_columns variable
		// will equal 2. This is fine for iterating w/ 0-indexed collections
		int num_columns = luis_utility::count_character(header, delim);


		std::vector<std::string> file_lines;

		while (!cities_file.eof())
		{
			std::string line;
			file_lines.emplace_back(std::getline(cities_file, line));
		}

		for (auto l : file_lines)
		{
			City c{ l };

			std::map<std::string, Flower> city_flowers;

			for (auto f : c.m_flowers)
			{
				Flower flower = flower_map.find(f)->second;
				city_flowers.emplace(flower.GetName(), flower);
			}

			m_flower_market.emplace(c.GetName(), city_flowers);
		}
		cities_file.close();
	}
}

void Market::InitRarityMap()
{
	std::string filename = "Resources\\RarityValues.txt";
	std::ifstream file(filename, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename << std::endl;
	}
	else
	{
		constexpr char delim = '|';
		std::string header;
		std::getline(file, header);

		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);

			std::string rarity_key;
			std::string min_price;
			std::string max_price;
			std::string min_quantity;
			std::string max_quantity;

			std::istringstream iss(line);
			std::getline(iss, rarity_key, delim);
			std::getline(iss, min_price, delim);
			std::getline(iss, max_price, delim);
			std::getline(iss, min_quantity, delim);
			std::getline(iss, max_quantity, delim);

			RarityValues p_vals = RarityValues{};

			p_vals.rarity_key = static_cast<Rarity>(std::stoi(rarity_key));
			p_vals.min_price = static_cast<double>(std::stof(min_price));
			p_vals.max_price = static_cast<double>(std::stof(max_price));
			p_vals.min_quantity = static_cast<int>(std::stoi(min_quantity));
			p_vals.max_quantity = static_cast<int>(std::stoi(max_quantity));

			m_rarity_map.emplace(p_vals.rarity_key, p_vals);

		}
		file.close();
	}
}
