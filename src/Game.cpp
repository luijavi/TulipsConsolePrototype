#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>

#include "Utility.h"
#include "Game.h"
#include "Flower.h"



Game::Game()
	:
	m_has_quit(false),
	m_day_num(0),
	m_current_city(nullptr)
{
	LoadCities();
	//LoadRandomEncounters(); // Implement later
	LoadFlowers();
	SetRarityValues();

}

Game::~Game()
{
}

// Includes main game loop and exit conditions. If the game has just started,
// and m_day_num is 0, then it initializes the game to start in Chicago, along
// with starting cash and health.
void Game::Run()
{
	while (!m_has_quit)
	{
		// Initializes a new game if m_day_num is 0
		if (m_day_num == 0)
		{
			m_current_city = m_cities.find("Chicago")->second;

			std::cout << "You withdraw your entire lifesavings to start trading in illicit flowers...\n";
			m_player.IncreaseCash(5000);
			m_player.IncreaseHealth(100);

			std::cout << "Your cash account has gone up by ";
			
			std::cout << luis_fmt::to_cash(m_player.GetCash()) << "\n\n";
			
			m_current_city->UpdateMarketPrices(rarity_values);
			
			++m_day_num;
		}

		DisplayStats();
		DisplayMenu();
		ProcessInput();
	}
}

// 
void Game::DisplayStats()
{
	std::cout << "STATUS\n"
			  << "======================================================================\n"
			  << "Day number: " << m_day_num << "\n"
			  << "Current city: " << m_current_city->GetNameAndCountry() << "\n"
			  << "Health: " << m_player.GetHealth() << "\n"
			  << "Cash: " << luis_fmt::to_cash(m_player.GetCash()) << "\n"
			  << "======================================================================\n\n";
}

void Game::DisplayMenu()
{
	std::cout << "MENU\n"
			  << "======================================================================\n"
		      << "[N]ext day\t" << "[F]ly away\t" << "[I]nventory\t" << "[M]arket\t" << "[Q]uit\t\n"
			  << "======================================================================\n";
}

// Gets user input for the main menu
void Game::ProcessInput()
{
	std::string line;
	std::cout << "> ";
	
	if (!std::getline(std::cin, line))
	{
		std::cout << "Error!\n";
	}
	std::cout << "\n";
	char player_choice = std::toupper(line[0]);

	switch (player_choice)
	{
		case 'N':
		{
			// Execute Next Day 
			NextDay();
		} break;

		case 'F':
		{
			// Fly away
			FlyAway();
		} break;

		case 'I':
		{
			// Inventory
			m_player.OpenInventory();
		} break;

		case 'M':
		{
			// Market
			std::cout << "Market\n" << std::endl;
			m_current_city->OpenMarket(m_player);
			std::cout << std::endl;
		} break;

		case 'Q':
		{
			// Quit
			std::cout << "Thanks for playing!\n" << std::endl;
			m_has_quit = true;

		} break;

		default:
		{
			std::cout << "Invalid entry!\n" << std::endl;
		}
	}

}


// TODO: This might have to be deleted. Currently not being used.
bool Game::RollForRandomEncounter()
{
	const unsigned short threshold = 30;
	
	std::random_device rd;
	std::uniform_int_distribution<int> distribution(1, 100);
	std::mt19937_64 engine(rd());

	int value = distribution(engine);

	return value < threshold;
}

// Loads and parses CitiesList.txt file, which includes the details to fill
// a City object.
void Game::LoadCities()
{
	std::string filename = "Resources\\CitiesList.txt";
	std::ifstream file{ filename, std::ios::in };

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename << std::endl;
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
				std::istringstream city_data(line);

				// TODO: Is this bad? emplacing a "new" City?
				m_cities.emplace(City(line).GetName(), new City(line));
			}
		}
		
		file.close();
	}


}

// TODO: Currently not being used...
void Game::LoadRandomEncounters()
{
	std::string filename = "Resources\\RandomEncounters.txt";
	std::ifstream file{ filename, std::ios::in };

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename << std::endl;
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
				std::stringstream encounter_data{ line };
				
			}
		}
	}
}

// Loads and parses FlowersList.txt file, which is used to fill a Flower object (which is
// owned by the city objects
void Game::LoadFlowers()
{
	std::string filename = "Resources\\FlowersList.txt";
	std::ifstream file{ filename, std::ios::in };

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename << std::endl;
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
				std::istringstream flower_data(line);
				std::string name;
				std::string rarity;
				std::string longevity;
				std::string hotness;
				std::string cities;

				std::getline(flower_data, name, '|');
				std::getline(flower_data, rarity, '|');
				std::getline(flower_data, longevity, '|');
				std::getline(flower_data, hotness, '|');
				std::getline(flower_data, cities, '|');

				Flower f = {};

				f.SetName(name);
				f.SetRarity(static_cast<Rarity>(std::stoi(rarity)));
				f.SetLongevity(std::stoi(longevity));
				f.SetHotness(std::stoi(hotness));

				m_flowers.emplace(name, f);

				if (cities == "*")
				{
					for (auto& c : m_cities)
					{
						c.second->AddFlower(&(m_flowers.find(name)->second));
					}
				}
				else if (cities == "none")
				{
					continue;
				}
				else
				{
					std::istringstream cities_line(cities);
					std::string c;

					while (std::getline(cities_line, c, '#') && !cities_line.eof())
					{
						m_cities.find(c)->second->AddFlower(&(m_flowers.find(name)->second));
					}
				}
			}
		}

		file.close();
	}
}

// Loads and parses RarityValues.txt file, and sets the rarity values for each
// flower
void Game::SetRarityValues()
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

				rarity_values.emplace(p_vals.rarity_key, p_vals);
			}
		}
		file.close();
	}
}

void Game::NextDay()
{
	++m_day_num;
	if (RollForRandomEncounter())
	{
		std::cout << "Random Encounter!" << std::endl;
	}
	m_current_city->UpdateMarketPrices(rarity_values);
}

void Game::FlyAway()
{
	bool valid_answer = false;
	while (!valid_answer)
	{
		std::cout << "FLY AWAY\n"
			<< "======================================================================\n"
			<< "DESTINATION CITY\n"
			<< "======================================================================\n";

		unsigned short option_num = 1;
		std::vector<std::string> city_options;
		
		for (const auto& c : m_cities)
		{
			if (c.second->GetName() == m_current_city->GetName())
			{
				continue;
			}
			else
			{
				std::cout << option_num << ". " << c.second->GetNameAndCountry() << std::endl;
				city_options.push_back(c.second->GetName());
				++option_num;
			}
		}
		
		std::cout << "\nWhere would you like to fly to? Select an option between 1 and " 
			<< option_num << " or [E] to go back.\n";


		std::cout << "> ";
		std::string player_choice;
		std::getline(std::cin, player_choice);
		std::cout << "\n";

		if (std::toupper(player_choice.at(0)) == 'E')
		{
			return;
		}
		else if (player_choice.empty() 
			     || std::all_of(player_choice.begin(), player_choice.end(), ::isalpha)
			     || std::all_of(player_choice.begin(), player_choice.end(), ::iscntrl))
		{
			std::cout << "Invalid answer!\n";
		}
		else if (std::stoi(player_choice) < option_num)
		{
			m_current_city = m_cities.at(city_options.at(std::stoi(player_choice) - 1));
			++m_day_num;
			m_current_city->UpdateMarketPrices(rarity_values);
			valid_answer = true;
		}
		else
		{
			std::cout << "Invalid answer!\n";
		}
	}
}
