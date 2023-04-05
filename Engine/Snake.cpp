#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	for(int i = nSegments - 1; i > 0; --i)
	{
		segments[i].FollowPrevSeg(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < MAX_nSEGMENTS)
	{
		segments[nSegments].InitBody();
		nSegments++;
	}
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

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

Location Snake::GetNextHeadLoc(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);

	return l;
}

void Snake::Segments::InitHead(const Location& in_location)
{
	loc = in_location;
	c = Snake::headColor;
}

void Snake::Segments::InitBody()
{
	c = Snake::bodyColor;
}

void Snake::Segments::FollowPrevSeg(const Segments& next) //looks at the previous snake segments location and moves to it
{
	loc = next.loc;
}

void Snake::Segments::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1); //checks the move is valid as the only valid delta has to have either -1 or 1, the other will always be 0 so it will always = 1
	loc.Add(delta_loc);
}

void Snake::Segments::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}
const Location& Snake::Segments::GetLocation() const
{
	return loc;
}