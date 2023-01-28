#pragma once

#include <string>
#include <vector>

enum class EncounterTrigger { kNextDay, kFlyAway, kBoth };

class RandomEncounter
{
public:
	RandomEncounter(const std::string& encounter_data);
private:
	EncounterTrigger m_turn_type;
	unsigned short m_probability;
	std::vector<std::string> m_effects;
	std::string m_text;
};