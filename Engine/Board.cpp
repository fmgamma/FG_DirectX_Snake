#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{

}

void Board::DrawCell(const Location& loc, Color c)
{
	//assert that all the tiles for our board are within the maximums we set in the header file
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	//offset values for drawing a border around our board
	const int offset_x = x + borderWidth + borderPadding;
	const int offset_y = y + borderWidth + borderPadding;

	gfx.DrawRectDim(loc.x * dimension + offset_x, loc.y * dimension + offset_y, dimension, dimension, c);

}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

//checks the snake is still inside the board
bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= 0 && loc.x < width &&
		   loc.y >= 0 && loc.y < height;
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (borderWidth + borderPadding) * 2 + height * dimension;
	const int right = left + (borderWidth + borderPadding) * 2 + width * dimension;

	//top border line
	gfx.DrawRect(left, top, right, top + borderWidth, borderColor);

	//left border line
	gfx.DrawRect(left, top + borderWidth, left + borderWidth, bottom - borderWidth, borderColor);

	//right border line
	gfx.DrawRect(right - borderWidth, top + borderWidth, right, bottom - borderWidth, borderColor);

	//bottom border line
	gfx.DrawRect(left, bottom - borderWidth, right, bottom, borderColor);
}