#pragma once
#include <map>
#include <string>

// Rankings determined by the player score. One of the main mechanics
// (Work your way up the criminal flower underworld
//enum class Ranks
//{
//	kFlowerPedler = 1
//};

// Forward declarations
class Flower;
class Market;

class Player
{
public:
	Player();
	~Player();
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	Player(Player&&) = delete;

	void AdjustHealth(int amount);
	void AdjustCash(int amount);

	void IncreaseHealth(int amount);
	void DecreaseHealth(int amount);

	void IncreaseCash(double amount);
	void DecreaseCash(double amount);

	const double GetHealth() const;
	const double GetCash() const;
	void SetHealth(int amount);
	void SetCash(double amount);

	void AddFlower(const Flower& flower, int quantity);
	void RemoveFlower(const Flower& flower, int quantity);

	void Buy(Market& market);
	void Sell(Market& market);

	void OpenInventory();
private:
	static constexpr unsigned short kMaxHealth = 100;
	static constexpr unsigned short kMinHealth = 0;
	int m_health;
	double m_cash;

	std::map<std::string, class Flower> m_flowers;
};