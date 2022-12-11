#pragma once
#include <map>
#include <string>

class Player
{
public:
	Player();

	void AdjustHealth(int amount);
	void AdjustCash(int amount);

	void IncreaseHealth(int amount);
	void DecreaseHealth(int amount);

	void IncreaseCash(double amount);
	void DecreaseCash(double amount);

	const double GetHealth() const;
	const double GetCash() const;

	void AddFlower(const class Flower& flower, int quantity);

	void OpenInventory();
private:
	static constexpr unsigned short kMaxHealth = 100;
	static constexpr unsigned short kMinHealth = 0;
	int m_health;
	double m_cash;

	std::map<std::string, class Flower> m_flowers;
};