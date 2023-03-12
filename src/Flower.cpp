#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>

#include "Flower.h"
#include "luis_utility/Utility.h"

Flower::Flower()
	:
	m_name(""),
	m_rarity(Rarity::kCommon),
	m_longevity(0),
	m_hotness(0),
	m_price(0.0),
	m_quantity(0)
{
}

Flower::Flower(std::istringstream& data)
	:
	m_price(0.0),
	m_quantity(0)
{
	const char delim = '|';
	std::getline(data, m_name, delim);
	
	std::string rarity;
	std::string longevity;
	std::string hotness;
	std::string cities;

	std::getline(data, rarity, delim);
	std::getline(data, longevity, delim);
	std::getline(data, hotness, delim);
	std::getline(data, cities, delim);

	m_rarity = static_cast<Rarity>(std::stoi(rarity));
	m_longevity = std::stoi(longevity);
	m_hotness = std::stoi(hotness);

	std::istringstream cities_data(cities);

	while (!cities_data.eof())
	{
		std::string c;
		std::getline(cities_data, c, '#');
		m_cities.insert(c);
	}
}

std::string Flower::GetName() const
{
	return m_name;
}

const Rarity Flower::GetRarity() const
{
	return m_rarity;
}

const Longevity Flower::GetLongevity() const
{
	return m_longevity;
}

const Hotness Flower::GetHotness() const
{
	return m_hotness;
}

const double Flower::GetPrice() const
{
	return m_price;
}

const int Flower::GetQuantity() const
{
	return m_quantity;
}

void Flower::LowerQuantity(int quantity)
{
	assert(quantity < m_quantity);
	m_quantity -= quantity;
}

void Flower::IncreaseQuantity(int quantity)
{
	assert(quantity > 0);
	m_quantity += quantity;
}

void Flower::IncreasePrice(double amount)
{
	assert(amount > 0);
	m_price = luis_math::add_without_overflow(m_price, amount);
}

void Flower::LowerPrice(double amount)
{
	assert(amount < m_price);
	m_price = luis_math::sub_without_underflow(m_price, amount);
}


void Flower::SetName(std::string_view name)
{
	m_name = name;
}

void Flower::SetRarity(Rarity rarity)
{
	assert(rarity >= Rarity::kCommon && rarity <= Rarity::kUnique && "Rarity does not exist!\n");
	m_rarity = rarity;
}

void Flower::SetRarity(int rarity)
{
	SetRarity(static_cast<Rarity>(rarity));
}

void Flower::SetLongevity(Longevity longevity)
{
	m_longevity = longevity;
}

void Flower::SetHotness(Hotness hotness)
{
	m_hotness = hotness;
}

void Flower::SetPrice(double price)
{
	assert(price > 0 && "Buy price can't be negative!\n");

	m_price = price;
}

void Flower::SetQuantity(int quantity)
{
	assert(quantity >= 0 && "Quantity cannot be negative!\n");
	m_quantity = quantity;
}
