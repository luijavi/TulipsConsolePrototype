#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>

#include "luis_utility/Utility.h"
#include "City.h"
#include "Flower.h"
#include "Player.h"

City::City(std::string_view city_data)
{
	std::istringstream iss(std::string(city_data), std::ios::in);
	constexpr char delim = '|';
	constexpr char sub_delim = '#';

	std::getline(iss, m_name, delim);
	std::getline(iss, m_country, delim);
	std::getline(iss, m_syndicate, delim);
	std::getline(iss, m_texture_filename, delim);

	// TODO: This may have to be moved elsewhere, since it's unused currently
	std::string flowers;
	std::getline(iss, flowers, delim);

	AddFlowers(flowers);
}

City::City(std::string name, std::string country)
	:
	m_name(name),
	m_country(country)
{
}

std::string City::GetName() const
{
	return m_name;
}

std::string City::GetNameAndCountry() const
{
	std::string s = m_name + ", " + m_country;
	return s;
}

void City::AddFlower(std::string_view flower_name)
{
	m_flowers.emplace_back(flower_name);
}

void City::AddFlowers(std::string_view flowers)
{
	std::istringstream iss(std::string(flowers), std::ios::in);
	static constexpr char delim = '#';

	while (!iss.eof())
	{
		std::string flower;
		std::getline(iss, flower, delim);
		m_flowers.push_back(flower);
	}
}
