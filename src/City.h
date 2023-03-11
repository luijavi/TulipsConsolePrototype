#pragma once

#include <string>
#include <vector>
#include <map>

// Forward declarations for use in City class
class Player;
class Flower;
struct RarityValues;

class City
{
private:
	friend class Market;
public:
	City() = default;
	City(std::string_view city_data);
	City(std::string name, std::string country);

	std::string GetName() const;
	std::string GetNameAndCountry() const;

	void AddFlower(std::string_view flower_name);
	void OpenMarket(Player& player);
private:
	void AddFlowers(std::string_view flowers);
private:
	std::string m_name;
	std::string m_country;
	std::string m_syndicate;
	std::string m_texture_filename;

	std::vector<std::string> m_flowers;
};