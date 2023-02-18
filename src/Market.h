#pragma once

#include <map>
#include <string>
#include <random>

#include "Rarity.h"

class Market
{
private:
	// Map of Cities with their respective flowers, as well as the market data for the flowers
	typedef std::map<std::string, std::map<std::string, class Flower>> FlowerMarket;

	

public:
	Market(std::mt19937_64& random_engine);

	void Update();
private:
	void InitFlowerMarket();
	void InitRarityMap();
	void UpdateFlowerMarketData(Flower& flower);
	void UpdateFlowerPrice(Flower& flower);
	void UpdateFlowerQuantity(Flower& flower);
private:
	static FlowerMarket m_flower_market;
	static std::map<Rarity, RarityValues> m_rarity_map;
	std::mt19937_64& m_engine;
};