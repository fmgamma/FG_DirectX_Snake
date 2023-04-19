#pragma once

#include <random>

#include "Snake.h"
#include "Board.h"
#include "Pipeline.h"

class Goal
{
private:

	static constexpr Color c = Colors::Cyan;
	Location loc;
public:

	Goal(std::mt19937& rng, const Board& brd, const Snake& snake);

	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Draw(Board& brd) const;
	const Location& GetLocation() const;

};