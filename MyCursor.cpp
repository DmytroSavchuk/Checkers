#include "MyCursor.h"

MyCursor::MyCursor()
{
	cursorTexture.loadFromFile("Images\\cursor.png");
	cursorSprite.setTexture(cursorTexture);
}


MyCursor::~MyCursor()
{
}

void MyCursor::PressedLeftKey()
{
	cursorTexture.loadFromFile("Images\\cursor1.png");
	cursorSprite.setTexture(cursorTexture);
}

void MyCursor::ReleasedLeftKey()
{
	cursorTexture.loadFromFile("Images\\cursor.png");
	cursorSprite.setTexture(cursorTexture);
}

void MyCursor::PointChecker()
{
	cursorTexture.loadFromFile("Images\\CursorPoint.png");
	cursorSprite.setTexture(cursorTexture);
}

Sprite &MyCursor::GetSprite()
{
	return cursorSprite;
}
