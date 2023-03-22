#pragma once

#include <optional>
#include <functional>

#include "Flower.h"
#include "Player.h"

struct CallBack
{
	std::optional<std::function<void(Flower, int)>> AddFlower(Flower flower, int quantity) { ::AddFlower(flower, quantity); }
};