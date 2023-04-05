#pragma once

#include "Board.h"

/* Snake is built with two classes: Snake and Segments. Segments holds the individual tiles that make up the snake and Snake will be the object that has all the segments together and
   the rest of the game will only refer to the Snake class*/

class Snake
{
private:
	class Segments
	{
	public:
		void InitHead(const Location& loc);
		void InitBody();
		void FollowPrevSeg(const Segments& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};

private:
	static constexpr Color headColor = Colors::MakeRGB(11, 102, 35);
	static constexpr Color bodyColor = Colors::MakeRGB(63, 112, 77);
	static constexpr int MAX_nSEGMENTS = 100;
	Segments segments[MAX_nSEGMENTS];
	int nSegments = 1;

public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc); //we're using a delta value here so all the segments can be passed their new location at once
	void Grow();
	void Draw(Board& brd) const;
	bool IsInTileBesidesTail(const Location& target) const;

	Location GetNextHeadLoc(const Location& delta_loc) const;
};