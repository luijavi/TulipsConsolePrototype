#pragma once

#include <string>
#include <vector>
#include <map>
#include <sstream>

enum class EncounterTrigger { kNextDay, kFlyAway, kBoth, kInvalid };

enum class ImpactedEntity {kPlayer, kCity, kGame, kFlower, kInvalid };

class RandomEncounter
{
public:
	RandomEncounter(std::string_view encounter_data);
	RandomEncounter(EncounterTrigger trigger, std::string_view encounter_text, ImpactedEntity impacted_entity, unsigned short probability);
	
private:
	std::vector<std::string> m_callbacks;
	std::string m_text;
	EncounterTrigger m_encounter_trigger;
	ImpactedEntity m_impacted_entity;
	unsigned short m_probability;

	// Map for game entities with string key
	std::map<std::string, ImpactedEntity> m_entities_map
	{
		{"City", ImpactedEntity::kCity},
		{"Flower", ImpactedEntity::kFlower},
		{"Game", ImpactedEntity::kGame},
		{"Player", ImpactedEntity::kPlayer}
	};

	std::map<std::string, EncounterTrigger> m_triggers_map
	{
		{"next_day", EncounterTrigger::kNextDay},
		{"travel", EncounterTrigger::kFlyAway},
		{"*", EncounterTrigger::kBoth}
	};
};