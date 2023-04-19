#pragma once

#include "Graphics.h"

//functions for each sprite needed for the game states, save your PC 5 minutes of being froze up and don't open the .cpp file
class SpriteCodex
{
public:
	static void DrawGameOver( int x,int y,Graphics& gfx );
	static void DrawTitle( int x,int y,Graphics& gfx );
	static void DrawHowToPlay(int x, int y, Graphics& gfx);
};