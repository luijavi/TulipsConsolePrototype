#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>
#include "Flower.h"

Flower::Flower()
	:
	m_name(""),
	m_rarity(Rarity::kCommon),
	m_longevity(0),
	m_hotness(0),
	m_buy_price(0.0),
	m_sell_price(0.0),
	m_quantity(0)
{
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

const double Flower::GetBuyPrice() const
{
	return m_buy_price;
}

const double Flower::GetSellPrice() const
{
	return m_sell_price;
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

void Flower::SetBuyPrice(double buy_price)
{
	assert(buy_price > 0 && "Buy price can't be negative!\n");

	m_buy_price = buy_price;
}

void Flower::SetSellPrice(double sell_price)
{
	assert(sell_price > 0 && "Sell price cannot be negative!\n");

	m_sell_price = sell_price;
}

void Flower::SetQuantity(int quantity)
{
	assert(quantity >= 0 && "Quantity cannot be negative!\n");
	m_quantity = quantity;
}
