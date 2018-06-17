#include "Hint.h"



Hint::Hint()
{
	hintTexture.loadFromFile("Images\\Cross1.png");
	hintSprite.setTexture(hintTexture);

}


Hint::~Hint()
{
}

Sprite & Hint::GetSprite()
{
	return hintSprite;
}

void Hint::SetPosition(int x, int y)
{
	xPos = x;
	yPos = y;
	hintSprite.setPosition((float)xPos, (float)yPos);
	hintSprite.setColor(Color::White);
	active = true;
}

void Hint::SetActive(bool x)
{
	active = x;
}

bool Hint::GetActive()
{
	return active;
}
