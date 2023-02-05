#pragma once

#include <iostream>

enum class MainMenuOptions
{
	kInvalid = 0,
	kNextDay,
	kFlyAway,
	kInventory,
	kMarket,
	kQuit
};


class Menu
{
public:
	Menu();
	~Menu();

	void Display();

private:

};