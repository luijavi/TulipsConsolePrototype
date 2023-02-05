#include "RandomEncounter.h"


RandomEncounter::RandomEncounter(std::string_view encounter_data)
{
	std::istringstream iss(static_cast<std::string>(encounter_data));

	constexpr char delim = '|';
	constexpr char sub_delim = '#';

	std::string trigger_string;
	std::string entity_string;
	std::string callbacks;
	std::string probability;

	std::getline(iss, trigger_string, delim);
	std::getline(iss, entity_string, delim);
	std::getline(iss, callbacks, delim);
	std::getline(iss, probability, delim);
	std::getline(iss, m_text, delim);

	// Add callback names to vector. There may be multiple, delimited with a # char
	std::istringstream callback_stream(callbacks);

	while (!callback_stream.eof())
	{
		std::string c;
		std::getline(callback_stream, c, sub_delim);
		m_callbacks.push_back(c);
	}

	// Set the event trigger member
	auto trigger_it = m_triggers_map.find(trigger_string);
	m_encounter_trigger = trigger_it != m_triggers_map.end() ? trigger_it->second : EncounterTrigger::kInvalid;

	// Set impacted entity
	auto entity_it = m_entities_map.find(entity_string);
	m_impacted_entity = entity_it != m_entities_map.end() ? entity_it->second : ImpactedEntity::kInvalid;

	m_probability = std::stoi(probability);
}

// TODO: Maybe this will have to be removed if it's not actually being used.
RandomEncounter::RandomEncounter(EncounterTrigger trigger, std::string_view encounter_text, ImpactedEntity impacted_entity, unsigned short probability)
	:
	m_encounter_trigger(trigger),
	m_text(encounter_text),
	m_impacted_entity(impacted_entity),
	m_probability(probability)
{
}
