#include "Checker.h"

Checker::Checker()
{
	xPos = yPos = dame = playerSide = 0;
}

Checker::~Checker()
{

}

bool Checker::CheckingForClick(int x, int y)
{
	if (x >= xPos - 80 && x <= xPos + 80 && y >= yPos - 80 && y <= yPos + 80)
	{
		return true;
	}
	return false;
}

void Checker::SetPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}

Sprite & Checker::GetSprite()
{
	return checkerSprite;
}

void Checker::CreatingChecker(int Side)
{
	active = true;
	if (Side < 0  && !dame)
	{
		checkerTexture.loadFromFile("Images\\CheckerONE.png");
		playerSide = false;
	}
	else if (Side > 0 && !dame)
	{
		checkerTexture.loadFromFile("Images\\CheckerTWO.png");
		playerSide = true;
	}
	else if (Side < 0 && dame)
	{
		checkerTexture.loadFromFile("Images\\CheckerDameONE.png");
		playerSide = false;
	}
	else if (Side > 0 && dame)
	{
		checkerTexture.loadFromFile("Images\\CheckerDameTWO.png");
		playerSide = true;
	}
	checkerSprite.setTexture(checkerTexture);
	checkerSprite.setPosition((float)xPos, (float)yPos);
}
void Checker::SetActive(bool x)
{
	active = x;
}

bool Checker::GetActive()
{
	return active;
}

void Checker::SetDame(bool x)
{
	dame = x;
	if (playerSide)
		checkerTexture.loadFromFile("Images\\CheckerDameTWO.png");
	else
		checkerTexture.loadFromFile("Images\\CheckerDameONE.png");
}

bool Checker::GetDame()
{
	return dame;
}

bool Checker::GetPlayer()
{
	return playerSide;
}
