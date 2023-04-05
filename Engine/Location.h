#pragma once

class Location
{
public:

	void Add(const Location& locVal)
	{
		x += locVal.x;
		y += locVal.y;
	}
	bool operator==(const Location& rhs) const //equivolance operator for 'Location' because it obviously doesn't have one by default (took too long to realise that)
	{
		return x == rhs.x && y == rhs.y;
	}

	int x = 10;
	int y = 10;
};