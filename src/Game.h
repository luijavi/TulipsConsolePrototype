#pragma once
#include <map>
#include <string>
#include <list>
#include <set>

#include "Player.h"
#include "City.h"
#include "RandomEncounter.h"
// #include "Menu.h"

enum class MainMenuOptions
{
	kInvalid = 0,
	kNextDay,
	kFlyAway,
	kInventory,
	kMarket,
	kQuit
};

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void DisplayStats();
	void DisplayMenu();
	void ProcessInput();
	bool RollForRandomEncounter();

	void LoadCities();
	void LoadRandomEncounters();
	void LoadFlowers();
	void SetRarityValues();

	void NextDay();
	void FlyAway();
private:
	Player m_player;

	std::map<Rarity, RarityValues> rarity_values;

	std::list<RandomEncounter> m_encounters;

	std::map<std::string, City*> m_cities;
	City* m_current_city;

	std::map<std::string, class Flower> m_flowers;


	bool m_has_quit;
	unsigned int m_day_num;

};