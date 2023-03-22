#pragma once

#include "RandomEncounter.h"

#include <map>
#include <random>

class EncounterHandler
{
public:
	EncounterHandler(std::mt19937_64& random_engine);

	RandomEncounter& FetchRandomEncounter(const EncounterTrigger& trigger);
private:
	void InitRandomEncounters();
private:
	std::map<int, RandomEncounter> m_encounters;
	std::mt19937_64& m_engine;
};