#include "CheckerBoard.h"

CheckerBoard::CheckerBoard()
{
	boardTexture.loadFromFile("Images\\ChessF.jpg");
	boardSprite.setTexture(boardTexture);
}


CheckerBoard::~CheckerBoard()
{
}

void CheckerBoard::SetSize(int h, int w)
{
	height = h;
	wigth = w; 
}

void CheckerBoard::SetPosition(int x, int y)
{
	xPos = x;
	yPos = y;
	boardSprite.setPosition((float)xPos, (float)yPos);
}

Sprite &CheckerBoard::GetSprite()
{
	return boardSprite;
}

Checker &CheckerBoard::GetChecker(int number)
{
	return checkers[number];
}

Checker &CheckerBoard::SearchChecker(int x, int y)
{
	for (int i = 0; i < 24; i++)
	{
		if (x >= xPos - 80 && x <= xPos + 80 && y >= yPos - 80 && y <= yPos + 80)
		{
			return checkers[i];
		}
	}
}
