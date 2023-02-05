#include "Menu_UNUSED.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Display()
{
	std::cout << "MENU\n"
		<< "======================================================================\n"
		<< "[N]ext day\t" << "[F]ly away\t" << "[I]nventory\t" << "[M]arket\t" << "[Q]uit\t\n"
		<< "======================================================================\n";
}
