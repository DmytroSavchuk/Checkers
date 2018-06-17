#include "MainFunctions.h"

#define MAX 8
#define AMM 24

int board[MAX][MAX] = {
	0,-1,0,-1,0,-1,0,-1,
	-1,0,-1,0,-1,0,-1,0,
	0,-1,0,-1,0,-1,0,-1,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	1,0,1,0,1,0,1,0,
	0,1,0,1,0,1,0,1,
	1,0,1,0,1,0,1,0
};

Vector2i mousePos, masMousePos, currPos, battlePos, enemyPos, winCondition;
Vector2f objMousePos;
int numHint;

int main()
{
	RenderWindow window(VideoMode(1500, 1100), "Checkers!"/*, Style::Fullscreen*/);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	Image icon;
	icon.loadFromFile("Images//Icon.png");
	window.setIcon(80, 80, icon.getPixelsPtr());

	Font font;
	font.loadFromFile("Fonts//Times_New_Roman_Normal.ttf");

	SoundBuffer music;
	music.loadFromFile("Music//Sun_Goes_Down.ogg");
	Sound sound;
	sound.setBuffer(music);

	Text player;
	player.setFont(font);
	player.setCharacterSize(24);
	player.setFillColor(Color::White);
	player.setPosition(1300, 500);

	MyCursor cursor;
	Texture Field;

	Sprite SpriteField;
	Field.loadFromFile("Images//Field.jpg");
	SpriteField.setTexture(Field);
	
	CheckerBoard field;

	Hint *phint = new Hint[25], *phint1 = phint;

	field.SetPosition(50, 50);
	FormingField(field);

	Vector2i moveCoord[15];

	int str = 0, colum = 0;
	int var = 0;
	int dx, dy;
	int check = 0;
	int numCheck = 0;
	bool isMove = false, noneMove = false;
	bool Side = false;
	bool hitsDraw = false;
	bool happening, battle = false, move, beat = false;
	bool point = false;
	int numPoint;

	sound.play();

	while (window.isOpen())
	{
		Event event;
		
		mousePos = Mouse::getPosition(window);
		objMousePos = window.mapPixelToCoords(mousePos);
		masMousePos = MasCursorPos(objMousePos);
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) 
			{
				window.close();
			}
			if (!isMove)
			{
				for (int i = 0; i < 24; i++)
				{
					if (!Side && field.GetChecker(i).GetSprite().getGlobalBounds().contains(objMousePos.x, objMousePos.y) && field.GetChecker(i).GetActive() && !field.GetChecker(i).GetPlayer())
					{
						cursor.PointChecker();
						point = true;
						numPoint = i;
						break;
					}
					if (Side && field.GetChecker(i).GetSprite().getGlobalBounds().contains(objMousePos.x, objMousePos.y) && field.GetChecker(i).GetActive() && field.GetChecker(i).GetPlayer())
					{
						cursor.PointChecker();
						point = true;
						numPoint = i;
						break;
					}
				}
			}
			if (point)
			{
					if (!field.GetChecker(numPoint).GetSprite().getGlobalBounds().contains(objMousePos.x, objMousePos.y) && field.GetChecker(numPoint).GetActive())
					{
						cursor.ReleasedLeftKey();
						point = false;
					}
			}
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
			{

				cursor.PressedLeftKey();
				if (!isMove)
				currPos = masMousePos;
				for (int i = 0; i < 24; i++)
				{
					if (!battle && field.GetChecker(i).GetSprite().getGlobalBounds().contains(objMousePos.x, objMousePos.y) && field.GetChecker(i).GetActive())
					{
						if ((board[currPos.y][currPos.x] < 0 && !Side || board[currPos.y][currPos.x] > 0 && Side))
						{
							dx = objMousePos.x - field.GetChecker(i).GetSprite().getPosition().x;
							dy = objMousePos.y - field.GetChecker(i).GetSprite().getPosition().y;
							isMove = true;
							numCheck = i;
						}
					}
					else if (battle && currPos == battlePos && field.GetChecker(i).GetSprite().getGlobalBounds().contains(objMousePos.x, objMousePos.y) && field.GetChecker(i).GetActive())
					{
						if ((board[battlePos.y][battlePos.x] < 0 && !Side || board[battlePos.y][battlePos.x] > 0 && Side))
						{
							dx = objMousePos.x - field.GetChecker(i).GetSprite().getPosition().x;
							dy = objMousePos.y - field.GetChecker(i).GetSprite().getPosition().y;
							isMove = true;
							numCheck = i;
						}
					}
				}

			}
			if (isMove)
			{
				field.GetChecker(numCheck).GetSprite().setColor(Color::Red);
				field.GetChecker(numCheck).GetSprite().setPosition(objMousePos.x - dx, objMousePos.y - dy);
				field.GetChecker(numCheck).SetPosition(objMousePos.x - dx, objMousePos.y - dy);

				if (board[masMousePos.y][ masMousePos.x] != 0 && hitsDraw == false)
				{
					happening = CheckingEvent(masMousePos, Side, field.GetChecker(numCheck).GetDame());

					if (happening == true)battle = false;
					else battle = true;

					if (happening)
					{
						var = MoveHints(masMousePos, moveCoord, Side, field.GetChecker(numCheck).GetDame());
					}
					else
					{
						var = CheckerBattle(masMousePos, moveCoord, Side, field.GetChecker(numCheck).GetDame());
						beat = true;
					}
					if (var == 0)noneMove = true;

					numHint = PlacingHints(phint, moveCoord, var);
					hitsDraw = true;
				}
			}
			if (event.type == Event::MouseButtonReleased)
			{
				phint = phint1;
				if (CheckingPosHint(phint))
				{
					if (Side)
					{
						for (int i = 0; i < 8; i++)
						{
							if (masMousePos == Vector2i(i, 0) && board[currPos.y][currPos.x] > 0)
							{
								field.GetChecker(numCheck).SetDame(true);
							}
						}
					}
					else if (!Side)
					{
						for (int i = 0; i < 8; i++)
						{
							if (masMousePos == Vector2i(i, 7) && board[currPos.y][currPos.x] < 0)
							{
								field.GetChecker(numCheck).SetDame(true);
							}
						}
					}
					CheckerMove(phint, var, Side, battle, field, field.GetChecker(numCheck).GetDame());
					beat = false;
					if (currPos != masMousePos && !CheckingEvent(battlePos, !Side, field.GetChecker(numCheck).GetDame()))
					{
						battle = true;
						Side = !Side;
						beat = true;
					}
					else if (!beat && masMousePos == battlePos)
					{
						battle = false;
					}
				}
				if (var != 0)
				{
					field.GetChecker(numCheck).GetSprite().setPosition((float)(currPos.x + 1) * 113, (float)(currPos.y + 1) * 113);
					field.GetChecker(numCheck).SetPosition((float)(currPos.x + 1) * 113, (float)(currPos.y + 1) * 113);
					var = 0;
					battlePos = currPos;
				}
				if (noneMove == true)
				{
					field.GetChecker(numCheck).GetSprite().setPosition((float)(currPos.x + 1) * 113, (float)(currPos.y + 1) * 113);
					field.GetChecker(numCheck).SetPosition((float)(currPos.x + 1) * 113, (float)(currPos.y + 1) * 113);
					noneMove = false;
				}
				cursor.ReleasedLeftKey();
				field.GetChecker(numCheck).GetSprite().setColor(Color::White);
				isMove = false;
				hitsDraw = false;
			}
		}

		cursor.GetSprite().setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));

		window.clear();

		window.draw(SpriteField);

		window.draw(field.GetSprite());

		phint = phint1;

		for (int i = 0; i < var; i++)
		{
			if (phint->GetActive())
			window.draw(phint->GetSprite());
			phint++;
		}

		for (int i = 0; i < 24; i++)
		{
			window.draw(field.GetChecker(i).GetSprite());
		}

		if (Side)player.setString("WHITE");
		else player.setString("BLACK");

		window.draw(player);

		window.draw(cursor.GetSprite());

		window.display();

		winCondition = CheckingForWin(field);

		if (winCondition.x == 1 && winCondition.y == 1)
		{
			player.setString("Game is ended, Winner is BLACK");
			getchar();
			exit(1);
		}
		else if (winCondition.x == 1 && winCondition.y == 0)
		{
			player.setString("Game is ended, Winner is WHITE");
			getchar();
			exit(1);
		}
	}
	delete[] phint1;
	return 0;
}
