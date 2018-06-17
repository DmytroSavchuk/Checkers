#include <SFML/Graphics.hpp>

using namespace sf;

class Hint
{
private:
	int xPos;
	int yPos;
	bool active;
	Texture hintTexture;
	Sprite hintSprite;
public:
	Hint();
	~Hint();
	Sprite &GetSprite();
	void SetPosition(int x, int y);
	void SetActive(bool x);
	bool GetActive();
};

