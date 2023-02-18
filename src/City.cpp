#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>

#include "luis_utility/Utility.h"
#include "City.h"
#include "Flower.h"
#include "Player.h"

City::City(std::string_view city_data)
{
	std::istringstream iss(std::string(city_data), std::ios::in);
	constexpr char delim = '|';

	std::getline(iss, m_name, delim);
	std::getline(iss, m_country, delim);
	std::getline(iss, m_syndicate, delim);
	std::getline(iss, m_texture_filename, delim);

	// TODO: This may have to be moved elsewhere, since it's unused currently
	std::string flowers;
	std::getline(iss, flowers, delim);
	std::istringstream flowers_iss(flowers);


}

City::City(std::string name, std::string country)
	:
	m_name(name),
	m_country(country)
{
}

std::string City::GetName() const
{
	return m_name;
}

std::string City::GetNameAndCountry() const
{
	std::string s = m_name + ", " + m_country;
	return s;
}

void City::AddFlower(std::string_view flower_name)
{
	m_flowers.emplace_back(flower_name);
}

void City::OpenMarket(Player& player)
{
	//// TODO: Since the Player class also uses something similar to this, maybe make it its own thing?
	//// (The display of market and inventory, I mean)
	//int i = 1;
	//std::cout << "MARKET\n"
	//		  << "======================================================================\n"
	//		  << "FLOWER               QUANTITY               BUY                   \n"
	//		  << "======================================================================\n";
	//int padding1 = 19;

	//for (const auto& f : m_flowers)
	//{
	//	if (i > 9)
	//	{
	//		padding1 = 18;
	//	}

	//	std::cout << std::left << i << ". " << std::setw(padding1) << f->GetName()
	//			  << std::right << std::setw(6) << f->GetQuantity()
	//			  << std::setw(20) << luis_fmt::to_cash(f->GetBuyPrice()) << "\n";
	//	++i;
	//}

	//GetInput(player, i);
}

void City::UpdateMarketPrices(const std::map<Rarity, RarityValues>& rarity_values)
{
	// Create random device on the stack?
	std::random_device rd;
	
	for (auto& f : m_flowers)
	{
		// Get the rarity values struct for pricing and quantities
		RarityValues r = rarity_values.at(f->GetRarity());

		// Randomize prices
		std::uniform_real_distribution<double> price_range(r.min_price, r.max_price);
		std::mt19937_64 engine(rd());

		double buy_price = luis_math::round(price_range(engine), 0.01);
		f->SetBuyPrice(buy_price);

		std::uniform_int_distribution<int> quantity_range(r.min_quantity, r.max_quantity);
		int quantity = quantity_range(engine);
		f->SetQuantity(quantity);
	}
}

bool City::ProcessMarketEvent(Player& player, int choice)
{
	std::cout << "\nYou have chosen to purchase " << m_flowers[choice]->GetName() << ". Is this correct? (Y/N)\n";
	std::cout << "> ";
	std::string answer;
	std::getline(std::cin, answer);
	std::cout << "\n";


	if (std::toupper(answer[0]) == 'N')
	{
		return false;
	}
	else if (std::toupper(answer[0]) == 'Y')
	{
		std::cout << "How many would you like to purchase?" << std::endl;
		std::cout << "> ";
		std::string num_purchased_str;
		std::getline(std::cin, num_purchased_str);

		int num_purchased = std::stoi(num_purchased_str);

		if (num_purchased > m_flowers[choice]->GetQuantity())
		{
			std::cout << "Invalid quantity! Must be less than " << m_flowers[choice]->GetQuantity() << "\n\n";
			return false;
		}
		else if (!num_purchased)
		{
			return false;
		}
		else if ((num_purchased * m_flowers[choice]->GetBuyPrice()) > player.GetCash())
		{
			std::cout << "Insufficient funds!\n\n";
			return false;
		}
		else if (num_purchased_str.empty() || std::all_of(num_purchased_str.begin(), num_purchased_str.end(), ::isalpha))
		{
			std::cout << "Invalid response!\n\n";
			return false;
		}
		else
		{

			double purchase_amount = num_purchased * m_flowers[choice]->GetBuyPrice();

			std::cout << "\nYou have selected to purchase " << num_purchased << " " << m_flowers[choice]->GetName()
				<< " at " << luis_fmt::to_cash(m_flowers[choice]->GetBuyPrice())
				<< " for a total of " << luis_fmt::to_cash(purchase_amount) << ".\n";
			

			// TODO: Add purchase confirmation validation
			

			std::cout << "\nPress any key to continue...";
			std::cin.get();


			player.DecreaseCash(purchase_amount);
			player.AddFlower(*m_flowers[choice], num_purchased);
			m_flowers[choice]->LowerQuantity(num_purchased);
			return true;
		}
	}

	return false;
}

void City::GetInput(Player& player, int num_choices)
{
	// TODO: This should probably be it's own function
	bool valid_response = false;

	while (!valid_response)
	{
		std::cout << "\nEnter a value between 1 and " << (num_choices - 1) << " or type 'E' to [E]xit the market.\n";
		std::cout << "> ";
		std::string player_choice;
		std::getline(std::cin, player_choice);

		if (std::toupper(player_choice[0]) == 'E')
		{
			std::cout << "You've exited the Market!\n";
			valid_response = true;
			return;
		}
		else if ((std::stoi(player_choice) > 0) && (std::stoi(player_choice) < (num_choices - 1)))
		{
			if (ProcessMarketEvent(player, (std::stoi(player_choice) - 1)))
			{
				valid_response = true;
			}
		}
		else
		{
			std::cout << "\nInvalid response!\n";
		}
	}
}

void City::AddFlowers(std::istringstream flowers)
{
	static constexpr char delim = '#';

	while (!flowers.eof())
	{
		std::string flower;
		std::getline(flowers, flower, delim);
		m_flowers.push_back(flower);
	}
}
