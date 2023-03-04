#pragma once

#include <map>
#include <string>
#include <random>

#include "Rarity.h"

// Forward declaration(s)
class Player;

class Market
{
private:
	// Map of Cities with their respective flowers, as well as the market data for the flowers
	typedef std::map<std::string, std::map<std::string, class Flower>> FlowerMarket;

public:
	Market(std::mt19937_64& random_engine);

	void Update();
	void Display(std::string_view city);
	void OpenForBuy(std::string_view city, Player& player);

	const int GetOptionCount(std::string_view city) const;
private:
	void InitFlowerMarket();
	void InitRarityMap();
	void RandomizeFlowerMarketData(Flower& flower);
	void RandomizeFlowerPrice(Flower& flower);
	void RandomizeFlowerQuantity(Flower& flower);
	//void GetInput(Player& player, int num_choices);
	int GetPlayerResponse(const std::vector<std::string>& flower_names);
	void ProcessBuyEvent(std::string_view city, Player& player, std::string_view flower_name);
	Flower& GetFlowerFromMarket(std::string_view city, std::string_view flower_name);
private:
	static FlowerMarket m_flower_market;
	static std::map<Rarity, RarityValues> m_rarity_map;
	std::mt19937_64& m_engine;
};