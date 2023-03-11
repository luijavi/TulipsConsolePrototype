#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

#include "Market.h"
#include "Flower.h"
#include "City.h"
#include "Player.h"
#include "luis_utility/Utility.h"


Market::Market(std::mt19937_64& random_engine)
	:
	m_engine(random_engine)
{
	InitRarityMap();
	InitFlowerMarket();
}

//TODO: Might have to also pass the random_device to this function
void Market::Update()
{
	for (auto& city_map : m_flower_market)
	{
		for (auto& flower_map : city_map.second)
		{
			RandomizeFlowerMarketData(flower_map.second);
		}
	}
}

void Market::Display(std::string_view city)
{
	int i = 1;
	std::cout << "MARKET\n"
		<< "======================================================================\n"
		<< "FLOWER               QUANTITY               BUY                   \n"
		<< "======================================================================\n";
	int padding1 = 19;
	static constexpr int padding2 = 6;
	static constexpr int padding3 = 20;

	for (const auto& f : m_flower_market.find(std::string(city))->second)
	{
		if (i > 9)
		{
			padding1 = 18;
		}

		std::cout << std::left << i << ". " << std::setw(padding1) << f.second.GetName()
			<< std::right << std::setw(padding2) << f.second.GetQuantity()
			<< std::setw(padding3) << luis_fmt::to_cash(f.second.GetBuyPrice()) << "\n";
		++i;
	}
}

void Market::OpenForBuy(std::string_view city, Player& player)
{
	// TODO: Since the Player class also uses something similar to this, maybe make it its own thing?
	// (The display of market and inventory, I mean)
	int i = 1;
	std::cout << "MARKET\n"
		<< "======================================================================\n"
		<< "FLOWER               QUANTITY               BUY                   \n"
		<< "======================================================================\n";
	int padding1 = 19;
	static constexpr int padding2 = 6;
	static constexpr int padding3 = 20;
	std::vector<std::string> flower_names;

	for (const auto& f : m_flower_market.find(std::string(city))->second)
	{
		if (i > 9)
		{
			padding1 = 18;
		}

		flower_names.push_back(f.second.GetName());

		std::cout << std::left << i << ". " << std::setw(padding1) << f.second.GetName()
			<< std::right << std::setw(padding2) << f.second.GetQuantity()
			<< std::setw(padding3) << luis_fmt::to_cash(f.second.GetBuyPrice()) << "\n";
		++i;
	}

	int player_response = GetPlayerResponse(flower_names);

	if (player_response != 0)
	{
		std::string chosen_flower = m_flower_market.find(std::string(city))->second.find(flower_names.at(player_response - 1))->second.GetName();
		ProcessBuyEvent(city, player, chosen_flower);
	}
}

void Market::ProcessBuyEvent(std::string_view city, Player& player, std::string_view flower_name)
{
	
	bool valid_response = false;
	Flower& chosen_flower = GetFlowerFromMarket(city, flower_name);

	while (!valid_response)
	{
		std::cout << "\nHow many units of " << flower_name << " would you like to purchase? (Enter 'C' to cancel.)\n";
		std::cout << "> ";
		std::string response;
		std::getline(std::cin, response);

		if (!std::cin.eof() && luis_utility::is_numeric(response))
		{
			int units = std::stoi(response);
			double cost = units * chosen_flower.GetBuyPrice();

			if (!units || units > chosen_flower.GetQuantity())
			{
				std::cout << "\nInvalid quantity! Quantity must be between 1 and " << chosen_flower.GetQuantity() << ".\n";
				continue;
			}
			else if (cost > player.GetCash())
			{
				std::cout << "\nInsufficient funds!\n";
				continue;
			}
			else
			{
				std::cout << "\nYou have selected to purchase " << units
					<< " of " << flower_name
					<< " for a total cost of " << luis_fmt::to_cash(cost) << ".\n"
					<< "\nIs this correct? (Y/N) (Enter 'C' to cancel.)\n";
				std::cout << "> ";

				std::string confirmation;
				std::getline(std::cin, confirmation);
				bool transaction_complete = false;
				char c = confirmation[0];

				while (!transaction_complete)
				{
					if (!std::cin.eof())
					{
						switch (std::tolower(c))
						{
							case 'y':
							{
								chosen_flower.LowerQuantity(units);
								player.AddFlower(chosen_flower, units);
								player.DecreaseCash(cost);
								valid_response = true;
								transaction_complete = true;
							} break;
							case 'n':
							{
								std::cout << "\n\n";
								transaction_complete = true;
							} break;
							case 'c':
							{
								std::cout << "\nTransaction canceled!\n";
								valid_response = true;
								transaction_complete = true;
							} break;
							default:
							{
								std::cout << "\nInvalid answer! Please enter 'Y' or 'N' (or 'C' to cancel)...\n";
								std::cout << "> ";
								std::getline(std::cin, confirmation);
								c = confirmation[0];
							} break;
						}
					}
				}
			}
		}
		else if (std::tolower(response[0]) == 'c')
		{
			std::cout << "\nTransaction canceled!\n";
			valid_response = true;
		}
		else
		{
			std::cout << "\nInvalid argument! Not a number!\n";
			std::cin.clear();
		}
	}
}

Flower& Market::GetFlowerFromMarket(std::string_view city, std::string_view flower_name)
{
	return m_flower_market.find(std::string(city))->second.find(std::string(flower_name))->second;
}

const int Market::GetOptionCount(std::string_view city) const
{
	return m_flower_market.find(std::string(city))->second.size();
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
			std::getline(cities_file, line);
			file_lines.emplace_back(line);
		}

		for (auto l : file_lines)
		{
			City c{ l };
			std::map<std::string, Flower> city_flowers;

			for (auto f : c.m_flowers)
			{
				Flower flower = flower_map.find(f)->second;
				RandomizeFlowerMarketData(flower);
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

void Market::RandomizeFlowerMarketData(Flower& flower)
{
	RandomizeFlowerPrice(flower);
	RandomizeFlowerQuantity(flower);
}

void Market::RandomizeFlowerPrice(Flower& flower)
{
	auto min_price = m_rarity_map.find(flower.GetRarity())->second.min_price;
	auto max_price = m_rarity_map.find(flower.GetRarity())->second.max_price;
	std::uniform_real_distribution<double> price_range(min_price, max_price);

	double buy_price = luis_math::round(price_range(m_engine), 0.01);
	flower.SetBuyPrice(buy_price);
}

void Market::RandomizeFlowerQuantity(Flower& flower)
{
	auto min_quantity = m_rarity_map.find(flower.GetRarity())->second.min_quantity;
	auto max_quantity = m_rarity_map.find(flower.GetRarity())->second.max_quantity;
	std::uniform_int_distribution<int> quantity_range(min_quantity, max_quantity);
	int quantity = quantity_range(m_engine);
	flower.SetQuantity(quantity);
}

int Market::GetPlayerResponse(const std::vector<std::string>& flower_names)
{
	bool valid_response = false;
	const auto num_choices = flower_names.size();
	std::string input;
	int player_response = 0;

	while (!valid_response) 
	{
		std::cout << "\nEnter a value between 1 and " << num_choices << " or type 'E' to [E]xit the market.\n";
		std::cout << "> ";
		std::getline(std::cin, input);

		if (std::toupper(input[0]) == 'E')
		{
			std::cout << "You've exited the Market!\n";
			valid_response = true;
		}
		else if ((std::stoi(input) > 0) && (std::stoi(input) < num_choices))
		{
			player_response = std::stoi(input);
			valid_response = true;
		}
		else
		{
			std::cout << "\nInvalid response!\n";
		}
	}

	return player_response;
}
