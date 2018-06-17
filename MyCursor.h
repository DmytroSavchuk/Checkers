#include <SFML/Graphics.hpp>

using namespace sf;

class MyCursor
{
private:
	Sprite cursorSprite;
	Texture cursorTexture;
public:
	MyCursor();
	~MyCursor();
	void PressedLeftKey();
	void ReleasedLeftKey();
	void PointChecker();
	Sprite &GetSprite();
};

