#pragma once

#include <map>
#include <string>
#include <list>
#include <set>
#include <random>

#include "Player.h"
#include "City.h"
#include "Flower.h"
#include "EventHandler.h"
#include "Market.h"

enum class MainMenuOptions
{
	kInvalid = 0,
	kNextDay,
	kFlyAway,
	kInventory,
	kMarket,
	kQuit
};

enum class GameOverConditions
{
	kUndefined,
	kPlayerDead,
	kPlayerQuit
};

class Game
{
public:
	Game();
	~Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;

	void Run();

private:
	void InitNewGame();
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

	bool GameOver();
	bool PlayAgain(const GameOverConditions& reason);
	void ResetGame();
	bool ConfirmQuit();
private:
	EventHandler m_event_handler;
	std::random_device m_rd;
	std::mt19937_64 m_engine;

	Market m_market;

	static constexpr int kStartingHealth = 100;
	static constexpr double KStartingCash = 5000.0;
	const std::string kStartingCity = "Chicago";
	
	Player m_player;

	std::map<Rarity, RarityValues> m_rarity_values;

	std::map<std::string, City*> m_cities;
	City* m_current_city;

	std::map<std::string, Flower> m_flowers;


	bool m_has_quit;
	unsigned int m_day_num;

};