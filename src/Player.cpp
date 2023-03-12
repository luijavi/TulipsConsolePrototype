#include <iostream>
#include <iomanip>
#include <cassert>

#include "Player.h"
#include "Flower.h"
#include "luis_utility/Utility.h"

Player::Player()
	:
	m_health(0),
	m_cash(0)
{
}

Player::~Player()
{
}

void Player::AdjustHealth(int amount)
{
	amount < 0 ? DecreaseHealth(amount) : IncreaseHealth(amount);
}

void Player::AdjustCash(int amount)
{
	amount < 0 ? DecreaseCash(amount) : IncreaseCash(amount);
}

void Player::IncreaseHealth(int amount)
{
	if (amount < 0)
	{
		std::cerr << "Amount needs to be positive value!" << std::endl;
	}
	else
	{
		(m_health + amount) > kMaxHealth ? m_health = kMaxHealth : (m_health += amount);
	}
}

void Player::DecreaseHealth(int amount)
{
	if (amount < 0)
	{
		std::cerr << "Amount needs to be positive value!" << std::endl;	
	}
	else
	{
		(m_health - amount) < kMinHealth ? m_health = kMinHealth : (m_health -= amount);
	}
}

void Player::IncreaseCash(double amount)
{
	if (amount < 0)
	{
		std::cerr << "Amount needs to be positive value!" << std::endl;
	}
	else
	{
		m_cash += amount;
	}
}

void Player::DecreaseCash(double amount)
{
	if (amount < 0)
	{
		std::cerr << "Amount needs to be positive value!" << std::endl;
	}
	else
	{
		m_cash -= amount;
	}
}

const double Player::GetHealth() const
{
	return m_health;
}

const double Player::GetCash() const
{
	return m_cash;
}

void Player::SetHealth(int amount)
{
	assert(amount > 0);
	m_health = amount;
}

void Player::SetCash(double amount)
{
	assert(amount > 0.0);
	m_cash = amount;
}

void Player::AddFlower(Flower flower, int quantity)
{
	// Check whether player doesn't own flower and set quantity to 0
	if (m_flowers.find(flower.GetName()) == m_flowers.end())
	{
		m_flowers.emplace(flower.GetName(), flower);
		m_flowers.at(flower.GetName()).SetQuantity(0);
	}

	m_flowers.at(flower.GetName()).IncreaseQuantity(quantity);
}

void Player::RemoveFlower(const Flower& flower, int quantity)
{	
	if (m_flowers.find(flower.GetName()) != m_flowers.end())
	{
		// Create reference to the flower being acted on to make the rest of this code
		// easier to read.
		Flower& temp_flower = m_flowers.find(flower.GetName())->second;

		// First, make sure that the quantity in the argument is valid
		if (quantity > temp_flower.GetQuantity())
		{
			std::cout << "\nInvalid call! Quantity argument is greater than current flower quantity!\n";
		}
		// If the quantity being removed is the entirety of the specified
		// flower in the inventory, then just erase it from the map and
		// not just have it as zero. 
		else if (quantity == temp_flower.GetQuantity())
		{
			m_flowers.erase(flower.GetName());
		}
		else
		{
			temp_flower.LowerQuantity(quantity);
		}
	}
	else
	{
		// If player doesn't have the flower, then print an error.
		// TODO: This type of error handling might be too messy. Might have to adjust?
		std::cerr << "\nWarning! " << flower.GetName() << " not found! No changes made.\n";
	}
}

void Player::OpenInventory()
{
	int i = 1;
	std::cout << "INVENTORY\n"
		<< "======================================================================\n"
		<< "FLOWER               QUANTITY               SELL\n"
		<< "======================================================================\n";

	if (!m_flowers.size())
	{
		std::cout << "\nThere is nothing in your inventory! Press any key to exit... ";
		std::cin.get();
		std::cout << "\n\n";
	}
	else
	{

		static int padding_1 = 19;
		static constexpr int padding_2 = 6;
		static constexpr int padding_3 = 20;
		std::vector<std::string> flower_names;

		for (const auto& f : m_flowers)
		{
			if (i > 9)
			{
				padding_1 = 18;
			}

			flower_names.push_back(f.second.GetName());

			std::cout << std::left << i << ". " << std::setw(padding_1) << f.second.GetName()
				<< std::right << std::setw(padding_2) << f.second.GetQuantity()
				<< std::setw(padding_3) << luis_fmt::to_cash(f.second.GetSellPrice()) << "\n";
			++i;
		}

		int player_response = GetPlayerResponse(flower_names);

		if (player_response != 0)
		{
			ProcessSellEvent(flower_names.at(player_response));
		}
	}
}

int Player::GetPlayerResponse(const std::vector<std::string>& flower_names)
{
	bool valid_response = false;
	const auto num_choices = flower_names.size();
	std::string input;
	int player_response = 0;

	while (!valid_response)
	{
		std::cout << "\nEnter a value between 1 and " << num_choices << " to sell, or type 'E' to [E]xit the inventory.\n";
		std::cout << "> ";
		std::getline(std::cin, input);

		if (std::toupper(input[0]) == 'E')
		{
			std::cout << "You've exited your inventory!\n";
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

void Player::ProcessSellEvent(std::string_view flower_name)
{
	bool valid_response = false;
	Flower& chosen_flower = m_flowers.find(std::string(flower_name))->second;
	
	while (!valid_response)
	{
		std::cout << "\nHow many units of " << flower_name << " would you like to sell? (Enter 'C' to cancel.)\n";
		std::cout << "> ";
		std::string response;
		std::getline(std::cin, response);

		if (!std::cin.eof() && luis_utility::is_numeric(response))
		{
			int units = std::stoi(response);
			double sale_amount = units * chosen_flower.GetSellPrice();

			if (!units || units > chosen_flower.GetQuantity())
			{
				std::cout << "\nInvalid quantity! Quantity must be between 1 and " << chosen_flower.GetQuantity() << ".\n";
				continue;
			}

			std::cout << "\nYou have selected to sell " << units
				<< " of " << flower_name
				<< " for a total of " << luis_fmt::to_cash(sale_amount) << ".\n"
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
							IncreaseCash(sale_amount);
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
