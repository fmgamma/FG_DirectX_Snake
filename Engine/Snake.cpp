#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc)
{
	segments[0].InitHead(loc);
}

//constantly move the snake and all it's segments by the delta location (the last location inputted by the player, default is {1,0}
void Snake::MoveBy(const Location& delta_loc)
{
	for(int i = nSegments - 1; i > 0; --i)
	{
		segments[i].FollowPrevSeg(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

//increase the size of the snake by 1 if the snake isn't too big already
void Snake::Grow()
{
	if (nSegments < MAX_nSEGMENTS)
	{
		segments[nSegments].InitBody();
		nSegments++;
	}
}

//draw a coloured cell for every segment of the snake
void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

//checks if the snake is in a specific tile except for the last segment of the snake, as if the head is moving to the tails location, this should be considered a valid move
bool Snake::IsInTileBesidesTail(const Location& target) const
{
	for (int i = 0; i < nSegments - 1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

//checks if the snake is in a specific tile
bool Snake::IsInTile(const Location& target) const
{
	for (int i = 0; i < nSegments; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

//returns the next location of the snakes head, to see if a game rule is going to be triggered.
Location Snake::GetNextHeadLoc(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);

	return l;
}

//initialise first snake segment
void Snake::Segments::InitHead(const Location& in_location)
{
	loc = in_location;
	c = Snake::headColor;
}

//initialise all other snake segments
void Snake::Segments::InitBody()
{
	c = Snake::bodyColor;
}

//looks at the previous snake segments location and moves to it
void Snake::Segments::FollowPrevSeg(const Segments& next)
{
	loc = next.loc;
}

//checks the move is valid as the only valid delta has to have either -1 or 1, the other will always be 0 so it will always = 1
void Snake::Segments::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1); 
	loc.Add(delta_loc);
}

//draws a coloured cell at the location of every segment in the array
void Snake::Segments::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

//returns the location of a snake segment
const Location& Snake::Segments::GetLocation() const
{
	return loc;
}