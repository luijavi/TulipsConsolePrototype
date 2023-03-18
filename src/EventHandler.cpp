#include "EventHandler.h"

#include <fstream>
#include <iostream>
#include <sstream>


EventHandler::EventHandler(std::mt19937_64& random_engine)
	:
	m_engine(random_engine)
{
	InitRandomEncounters();
}

void EventHandler::InitRandomEncounters()
{
	std::string filename = "Resources\\RandomEncounters.txt";
	std::ifstream file{ filename, std::ios::in };

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename << std::endl;
	}
	else
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);

			if (line[0] == '$' || line.empty())
			{
				continue;
			}
			else
			{
				std::istringstream data(line);
				std::string id_string;
				std::string other_encounter_info;	// TODO: Rename this - basically, it's all the non-ID data

				std::getline(data, id_string, '|');
				std::getline(data, other_encounter_info);

				m_encounters.emplace(std::stoi(id_string), RandomEncounter(other_encounter_info));

			}
		}
	}
}