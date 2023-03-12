#pragma once

#include <string>
#include <string_view>
#include <set>

#include "Rarity.h"

// Typedefs for flower stats
typedef unsigned short Longevity;
typedef unsigned short Hotness;

class Flower
{
public:
	// TODO: Create parameterized constructors and maybe get rid of all these setters
	Flower();
	Flower(std::istringstream& data);

	// Getter(s)/Setter(s)
	void SetName(std::string_view name);
	void SetRarity(Rarity rarity);
	void SetRarity(int rarity);
	void SetLongevity(Longevity longevity);
	void SetHotness(Hotness hotness);
	void SetPrice(double price);
	void SetQuantity(int quantity);
	std::string GetName() const;
	const Rarity GetRarity() const;
	const Longevity GetLongevity() const;
	const Hotness GetHotness() const;
	const double GetPrice() const;
	const int GetQuantity() const;

	void LowerQuantity(int quantity);
	void IncreaseQuantity(int quantity);
	void IncreasePrice(double amount);
	void LowerPrice(double amount);
private:
	std::string m_name;
	Rarity m_rarity;
	Longevity m_longevity;
	Hotness m_hotness;
	double m_price;
	
	// TODO: Quantity should probably not be in Flower class
	int m_quantity;	

	// TODO: This may have to be moved out of the Flower and just live in the Market class
	std::set<std::string> m_cities;		
};