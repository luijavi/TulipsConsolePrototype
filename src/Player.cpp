#include "Player.h"
#include "Flower.h"
#include "luis_utility/Utility.h"
#include <iostream>
#include <iomanip>
#include <cassert>

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

void Player::AddFlower(const Flower& flower, int quantity)
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
	int padding1 = 19;

	for (const auto& f : m_flowers)
	{
		if (i > 9)
		{
			padding1 = 18;
		}

		std::cout << std::left << i << ". " << std::setw(padding1) << f.second.GetName()
			<< std::right << std::setw(6) << f.second.GetQuantity()
			<< std::setw(20) << luis_fmt::to_cash(f.second.GetSellPrice()) << "\n";
		++i;
	}

	std::cout << "\n\n";
}
