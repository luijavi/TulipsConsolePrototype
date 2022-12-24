#pragma once

#include <string>
#include <string_view>
#include <set>

// Typedefs for flower stats
typedef unsigned short Longevity;
typedef unsigned short Hotness;

enum class Rarity
{
	kCommon = 1,
	kUncommon,
	kRare,
	kLegendary,
	kMythic,
	kUnique
};

struct PriceRange
{
	double min_price;
	double max_price;
};

struct QuantityRange
{
	int min_quantity;
	int max_quantity;
};

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
	void SetBuyPrice(double buy_price);
	void SetSellPrice(double sell_price);
	void SetQuantity(int quantity);
	std::string GetName() const;
	const Rarity GetRarity() const;
	const Longevity GetLongevity() const;
	const Hotness GetHotness() const;
	const double GetBuyPrice() const;
	const double GetSellPrice() const;
	const int GetQuantity() const;

	void LowerQuantity(int quantity);
	void IncreaseQuantity(int quantity);
private:
	std::string m_name;
	Rarity m_rarity;
	Longevity m_longevity;
	Hotness m_hotness;
	double m_buy_price;
	double m_sell_price;
	int m_quantity;	// TODO: Quantity should probably not be in Flower class
	std::set<std::string> m_cities;
};


// Used to set the price and quantities at market
struct RarityValues
{
	Rarity rarity_key;
	double min_price;
	double max_price;
	int min_quantity;
	int max_quantity;
};