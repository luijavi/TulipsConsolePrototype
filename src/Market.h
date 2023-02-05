#pragma once

#include <map>
#include <string>

#include "Flower.h"

class Market
{
private:
	// Map of Cities with their respective flowers, as well as the market data for the flowers
	typedef std::map<std::string, std::map<std::string, struct FlowerData>> FlowerMarket;

	struct FlowerMarketData
	{

	};

public:
	Market();
	void InitFlowerMarket();
private:
	static FlowerMarket m_flower_market;
};