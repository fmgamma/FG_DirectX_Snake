#pragma once

class Location
{
public:

	void Add(const Location& locVal)
	{
		x += locVal.x;
		y += locVal.y;
	}

	int x = 10;
	int y = 10;
};