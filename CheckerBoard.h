#include <SFML/Graphics.hpp>
#include "Checker.h"

using namespace sf;

class CheckerBoard
{
private:
	int xPos, yPos;
	int height;
	int wigth;
	Texture boardTexture;
	Sprite boardSprite;
	Checker checkers[24];
public:
	CheckerBoard();
	~CheckerBoard();
	void SetSize(int h, int w);
	void SetPosition(int x, int y);
	Sprite &GetSprite();
	Checker &GetChecker(int number);
	Checker &SearchChecker(int x, int y);
};

