#pragma once

#include "RandomEncounter.h"

#include <map>
#include <random>

class EventHandler
{
public:
	EventHandler(std::mt19937_64& random_engine);
private:
	void InitRandomEncounters();
	void AddRandomEncounter();
private:
	std::map<int, RandomEncounter> m_encounters;
	std::mt19937_64& m_engine;
};