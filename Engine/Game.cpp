/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"
#include <sstream>
#include <stdlib.h>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake({ 16, 12 }),
	fruit(rng, brd, snake)
{ }

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
	{
		exit(0);
	}

	if (gameBegin)
	{
		if (!gameOver)
		{

			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				delta_loc = { 0,-1 };
			}

			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				delta_loc = { 0,1 };
			}

			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				delta_loc = { -1,0 };
			}

			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				delta_loc = { 1,0 };
			}

			++snakeMoveCounter;
			if (snakeMoveCounter >= snakeMovePerSec)
			{
				snakeMoveCounter = 0;
				const Location next = snake.GetNextHeadLoc(delta_loc);
				if (!brd.IsInsideBoard(next) || snake.IsInTileBesidesTail(next))
				{
					gameOver = true;
				}
				else
				{
					const bool eating = next == fruit.GetLocation();
					if (eating)
					{
						snake.Grow();
					}
					snake.MoveBy(delta_loc);
					if (eating)
					{
						fruit.Respawn(rng, brd, snake);
						scoreCounter++;
					}
				}
			}
			++snakeSpeedUpCounter;
			if (snakeSpeedUpCounter >= snakeSpeedUpPerSec)
			{
				snakeSpeedUpCounter = 0;
				snakeMovePerSec--;
				if (snakeMovePerSec < 0)
				{
					snakeMovePerSec = 0;
				}
			}
		}
	}
	else
	{
		//howToPlay = wnd.kbd.KeyIsPressed(0x48); DEPRECATED
		gameBegin = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
}

void Game::ComposeFrame()
{
	if (gameBegin)
	{
		snake.Draw(brd);
		fruit.Draw(brd);
		brd.DrawBorder();
		if (gameOver)
		{
			SpriteCodex::DrawGameOver(1, 1, gfx);	//TODO: make a title and game over screen, put game over screen here
		}
	}
	/*else if (howToPlay)
	{
		SpriteCodex::DrawHowToPlay(1, 1, gfx); DEPRECATED
	}*/
	else
	{
		SpriteCodex::DrawTitle(1, 1, gfx);
	}

	/*std::uniform_int_distribution<int> colorDist(0, 255); //OLD - Test code to draw the board and check it's working
	for (int y = 0; y < brd.GetGridHeight(); y++)
	{
		for (int x = 0; x < brd.GetGridWidth(); x++)
		{
			Location loc = { x, y };
			Color c(colorDist(rng), colorDist(rng), colorDist(rng));
			brd.DrawCell(loc, c);
		}
	}*/
}