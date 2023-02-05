#pragma once

#include "RandomEncounter.h"

#include <map>

class EventHandler
{
public:
	EventHandler();
private:
	void InitRandomEncounters();
	void AddRandomEncounter();
private:
	std::map<int, RandomEncounter> m_encounters;
};