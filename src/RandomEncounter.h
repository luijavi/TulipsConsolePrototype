 #pragma once

#include <string>
#include <optional>
#include <functional>
#include <map>

enum class EncounterTrigger { kNextDay, kFlyAway, kBoth };

class RandomEncounter
{
public:
	RandomEncounter(const std::string& encounter_data);
private:
	EncounterTrigger m_turn_type;
	unsigned short m_probability;
	std::string m_text;
};