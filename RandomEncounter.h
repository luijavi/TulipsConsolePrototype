#pragma once

#include <string>
#include <vector>

//enum class ImpactType { kNone, kIncrease, kDecrease };
//
//struct Effects
//{
//	int cash = 0;
//	int health = 0;
//	bool inventory_flower = false;
//	bool inventory_gun = false;
//	bool market_price = false;
//	bool other = false;
//};

enum class TurnType { kNextDay, kFlyAway, kBoth };

class RandomEncounter
{
public:
	RandomEncounter(const std::string& encounter_data);
private:
	TurnType m_turn_type;
	unsigned short m_probability;
	std::vector<std::string> m_effects;
	std::string m_text;
};