#include <SFML/Graphics.hpp>

using namespace sf;

class Checker
{
private:
	int xPos;
	int yPos;
	bool playerSide;
	bool dame;
	bool active;
	Texture checkerTexture;
	Sprite checkerSprite;
public:
	Checker();
	~Checker();
	bool CheckingForClick(int x, int y);
	void SetPosition(int x, int y);
	Sprite &GetSprite();
	void CreatingChecker(int Side);
	void SetActive(bool x);
	bool GetActive();
	void SetDame(bool x);
	bool GetDame();
	bool GetPlayer();

};

