#pragma once

#include <string>
#include <vector>
#include <map>
#include <sstream>

enum class EncounterTrigger { kInvalid, kNextDay = 1, kFlyAway, kBoth};

enum class ImpactedEntity { kInvalid, kPlayer = 1, kCity, kGame, kFlower};

class RandomEncounter
{
public:
	RandomEncounter(std::string_view encounter_data);
	RandomEncounter(EncounterTrigger trigger, std::string_view encounter_text, ImpactedEntity impacted_entity, unsigned short probability);
	void PrintMessage();
	const EncounterTrigger& GetTrigger() const;
	const unsigned short GetProbability() const;
	const ImpactedEntity& GetImpactedEntity() const;
private:
	std::vector<std::string> m_callbacks;
	std::string m_text;
	EncounterTrigger m_encounter_trigger;
	ImpactedEntity m_impacted_entity;
	unsigned short m_probability;
};