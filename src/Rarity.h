#pragma once

enum class Rarity
{
	kInvalid,
	kCommon,
	kUncommon,
	kRare,
	kLegendary,
	kMythic,
	kUnique
};

// Used to set the price and quantities at market
struct RarityValues
{
	Rarity rarity_key{ Rarity::kInvalid };
	double min_price{ 0.0 };
	double max_price{ 0.0 };
	double spread{ 0.0 };
	int min_quantity{ 0 };
	int max_quantity{ 0 };
};