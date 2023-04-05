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
#include "Sphere.h"
#include "TestTriangle.h"
//#include "CubeSkinScene.h"
//#include "CubeVertexColorScene.h"
//#include "CubeSolidScene.h"
//#include "DoubleCubeScene.h"
//#include "VertexWaveScene.h"
//#include "CubeVertexPositionColorScene.h"
//#include "CubeSolidGeometryScene.h"
//#include "CubeFlatIndependentScene.h"
//#include "GeometryFlatScene.h"
//#include "GouraudScene.h"
//#include "GouraudPointScene.h"
//#include "PhongPointScene.h"
#include "SpecularPhongPointScene.h"
#include <sstream>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake( {2,2})
{
	scenes.push_back( std::make_unique<SpecularPhongPointScene>( gfx ) );
	curScene = scenes.begin();
	OutputSceneName();
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
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
			if (!brd.IsInsideBoard(next) || snake.IsInTile(next))
			{
				gameOver = true;
			}
			else
			{
				if (wnd.kbd.KeyIsPressed(VK_CONTROL))
				{
					snake.Grow();
				}
				snake.MoveBy(delta_loc);
			}
		}
	}
}

void Game::CycleScenes()
{
	if( ++curScene == scenes.end() )
	{
		curScene = scenes.begin();
	}
	OutputSceneName();
}

void Game::ReverseCycleScenes()
{
	if( curScene == scenes.begin() )
	{
		curScene = scenes.end() - 1;
	}
	else
	{
		--curScene;
	}
	OutputSceneName();
}

void Game::OutputSceneName() const
{
	std::stringstream ss;
	const std::string stars( (*curScene)->GetName().size() + 4,'*' );

	ss << stars << std::endl 
		<< "* " << (*curScene)->GetName() << " *" << std::endl 
		<< stars << std::endl;
	OutputDebugStringA( ss.str().c_str() );
}

void Game::ComposeFrame()
{
	// draw scene
	//(*curScene)->Draw();

	snake.Draw(brd);
	if (gameOver)
	{
		//TODO: make a title and game over screen, put game over screen here
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