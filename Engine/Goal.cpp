#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	Respawn(rng, brd, snake);
}

//when a fruit has been eaten, it needs to respawn at a valid board location.
void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

	Location newLoc;

	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);

	} while (snake.IsInTile(newLoc));

	loc = newLoc;
}

//draws a coloured cell where the fruit is currently located
void Goal::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

//return the location of the current fruit
const Location& Goal::GetLocation() const
{
	return loc;
}
