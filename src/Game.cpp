#include <iostream>
#include <iomanip>
#include <fstream>

#include "luis_utility/Utility.h"
#include "Game.h"

Game::Game()
	:
	m_engine(m_rd()),
	m_market(m_engine),
	m_has_quit(false),
	m_day_num(0),
	m_current_city(nullptr),
	m_encounter_handler(m_engine)
{
	LoadCities();
	//LoadRandomEncounters(); // Implement later
	
	
	InitNewGame();
}

Game::~Game()
{
}

// Main game loop
void Game::Run()
{
	while (!GameOver())
	{
		DisplayStats();
		DisplayMenu();
		ProcessInput();
	}
}

void Game::InitNewGame()
{
	m_day_num = 0;

	// Intro message
	std::cout << "Welcome to Tulips of the Underground!\n\n";
	std::cout << "You've finally decided to try your hand at Botanical Black Market.\n\n";
	std::cout << "You withdraw your entire lifesavings to start trading in illicit flowers...\n";

	// Init city and player
	m_current_city = m_cities.find(kStartingCity)->second;
	m_player.SetCash(KStartingCash);
	m_player.SetHealth(kStartingHealth);

	std::cout << "Your cash account has gone up by ";

	std::cout << luis_fmt::to_cash(m_player.GetCash()) << "\n\n";
	m_market.Update();

	++m_day_num;
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
			m_market.OpenForBuy(m_current_city->GetName(), m_player);
			std::cout << std::endl;
		} break;

		case 'Q':
		{
			// Quit
			if (ConfirmQuit())
			{
				m_has_quit = true;
			}

		} break;

		default:
		{
			std::cout << "Invalid entry!\n" << std::endl;
		} break;
	}

}


// TODO: This might have to be deleted. Currently not being used.
bool Game::RollForRandomEncounter(const RandomEncounter& random_encounter)
{
	const unsigned short threshold = random_encounter.GetProbability();
	std::uniform_int_distribution<int> distribution(1, 100);
	int value = distribution(m_engine);

	return value < threshold;
}

void Game::HandleRandomEncounter(const RandomEncounter& random_encounter)
{
	if (random_encounter.GetImpactedEntity() == ImpactedEntity::kCity)
	{

	}
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

		file.close();
	}
}

void Game::NextDay()
{
	++m_day_num;
	m_market.Update();
	
	RandomEncounter& random_encounter = m_encounter_handler.FetchRandomEncounter(EncounterTrigger::kNextDay);
	if (RollForRandomEncounter(random_encounter))
	{
		HandleRandomEncounter(random_encounter);
	}
}

void Game::FlyAway()
{
	bool valid_answer = false;
	while (!valid_answer)
	{
		std::cout << "\nFLY AWAY\n"
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


		
		// Check that player choice is numeric
		if (player_choice.empty())
		{
			std::cout << "\nInvalid answer!\n";
		}
		else if (!std::all_of(player_choice.begin(), player_choice.end(), ::isdigit)
			|| player_choice.empty())
		{
			if (player_choice.at(0) == 'e' || player_choice.at(0) == 'E')
			{
				return;
			}
			else
			{
				std::cout << "\nInvalid answer!\n";
			}
		}
		else if (std::stoi(player_choice) > 0 && std::stoi(player_choice) < option_num)
		{
			m_current_city = m_cities.at(city_options.at(std::stoi(player_choice) - 1));
			++m_day_num;
			m_market.Update();
			valid_answer = true;
		}
		else
		{
			std::cout << "\nInvalid answer!\n";
		}
	}

	RandomEncounter& random_encounter = m_encounter_handler.FetchRandomEncounter(EncounterTrigger::kFlyAway);
	if (RollForRandomEncounter(random_encounter))
	{
		// random_encounter.Execute();
	}
}

void Game::ChangeCity(std::string_view city)
{
	if (m_current_city->GetName() != city)
	{
		m_current_city = m_cities.find(std::string(city))->second;
	}

	m_market.Update();
}

bool Game::GameOver()
{
	if (m_player.GetHealth() <= 0 && !PlayAgain(GameOverConditions::kPlayerDead))
	{
		return true;
	}
	else if (m_has_quit && !PlayAgain(GameOverConditions::kPlayerQuit))
	{
		return true;
	}

	return false;
}

bool Game::PlayAgain(const GameOverConditions& reason)
{
	std::string player_answer;
	
	// Print message
	switch (reason)
	{

		case GameOverConditions::kPlayerDead:
		{
			std::cout << "\nYou've died!\n";
		} break;

		case GameOverConditions::kPlayerQuit:
		{
			std::cout << "\nThanks for playing!\n";
		} break;
	}

	std::string answer;

	std::cout << "\nPlay again? (Y/N)\n"
		<< "> ";

	while (std::getline(std::cin, answer))
	{
		if (std::toupper(answer[0]) == 'Y')
		{
			ResetGame();
			return true;
		}
		else if (std::toupper(answer[0]) == 'N')
		{
			std::cout << "\nGoodbye!\n";
			return false;
		}
		else
		{
			std::cout << "\nInvalid answer!\n";
			std::cout << "\nPlay again? (Y/N)\n"
				<< "> ";
		}
	}

	return false;
}

void Game::ResetGame()
{
	InitNewGame();
}

bool Game::ConfirmQuit()
{
	std::cout << "\nAre you sure you want to quit? (Y/N)\n"
		      << "> ";

	std::string answer = "N";

	while (std::getline(std::cin, answer))
	{
		if (std::toupper(answer[0]) == 'Y')
		{
			return true;
		}
		else if (std::toupper(answer[0]) == 'N')
		{
			return false;
		}
		else
		{
			std::cout << "\nInvalid answer!\n";
			std::cout << "\nAre you sure you want to quit? (Y/N)\n"
				      << "> ";
		}
	}

	return false;
}
