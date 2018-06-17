#include "MainFunctions.h"

#define MAX 8
#define AMM 24

extern Vector2i mousePos, masMousePos, currPos, battlePos, enemyPos, winCondition;
extern Vector2f objMousePos;
extern int numHint;

extern int board[MAX][MAX];

int CheckerBattle(Vector2i Pos, Vector2i Coord[15], bool Side, bool dame)
{
	int x;
	int y;
	int number = 0, k;
	if (dame)k = 8;
	else k = 1;
	for (int i = 0; i < 4; i++)
	{
		x = Pos.x;
		y = Pos.y;
		for (int j = 0; x < 8 && x >= 0 && y < 8 && y >= 0 && j < k; j++)
		{
			if (i == 0)
			{
				x = x + 1;
				y = y + 1;
			}
			else if (i == 1)
			{
				x = x - 1;
				y = y + 1;

			}
			else if (i == 2)
			{
				x = x + 1;
				y = y - 1;
			}
			else if (i == 3)
			{
				x = x - 1;
				y = y - 1;
			}

			if (i == 0 && ((board[y][x] > 0 && board[y + 1][x + 1] == 0 && Side == false) || (board[y][x] < 0 && board[y + 1][x + 1] == 0 && Side == true)) && x + 1 < MAX && y + 1 < MAX)
			{
				for (int j = 0; x < 8 && x >= 0 && y < 8 && y >= 0 && j < k; x = x + 1, y = y + 1, j++)
				{
					if (board[y + 1][x + 1] == 0 && x + 1 < MAX && y + 1 < MAX)
						Coord[number++] = Vector2i(x + 1, y + 1);
					else
					{
						//i++;
						break;
					}
				}
			}
			else if (i == 1 && ((board[y][x] > 0 && board[y + 1][x - 1] == 0 && Side == false) || (board[y][x] < 0 && board[y + 1][x - 1] == 0 && Side == true)) && x - 1 >= 0 && y + 1 < MAX)
			{
				for (int j = 0; x < 8 && x >= 0 && y < 8 && y >= 0 && j < k; x = x - 1, y = y + 1, j++)
				{
					if (board[y + 1][x - 1] == 0 && x - 1 >= 0 && y + 1 < MAX)
						Coord[number++] = Vector2i(x - 1, y + 1);
					else
					{
						//i++;
						break;
					}
				}
			}
			else if (i == 2 && ((board[y][x] > 0 && board[y - 1][x + 1] == 0 && Side == false) || (board[y][x] < 0 && board[y - 1][x + 1] == 0 && Side == true)) && x + 1 < MAX && y - 1 >= 0)
			{
				for (int j = 0; x < 8 && x >= 0 && y < 8 && y >= 0 && j < k; x = x + 1, y = y - 1, j++)
				{
					if (board[y - 1][x + 1] == 0 && x + 1 < MAX && y - 1 >= 0)
						Coord[number++] = Vector2i(x + 1, y - 1);
					else
					{
						//i++;
						break;
					}
				}
			}
			else if (i == 3 && ((board[y][x] > 0 && board[y - 1][x - 1] == 0 && Side == false) || (board[y][x] < 0 && board[y - 1][x - 1] == 0 && Side == true)) && x - 1 >= 0 && y - 1 >= 0)
			{
				for (int j = 0; x < 8 && x >= 0 && y < 8 && y >= 0 && j < k; x = x - 1, y = y - 1, j++)
				{
					if (board[y - 1][x - 1] == 0 && x - 1 >= 0 && y - 1 >= 0)
						Coord[number++] = Vector2i(x - 1, y - 1);
					else
					{
						//i++;
						break;
					}
				}
			}
		}
	}
	return number;
}


void CheckerMove(Hint *p, int& var, bool& Side, bool battle, CheckerBoard& field, bool dame)
{
	Hint *phit = p;
	int x;
	int y;
	int offsetX;
	int offsetY;
	for (int i = 0; i < var; i++)
	{
		if (phit->GetSprite().getGlobalBounds().contains(objMousePos.x, objMousePos.y) && phit->GetActive())
		{
			for (int i = 0; i < var; i++)
			{
				phit->GetSprite().setColor(Color::Transparent);
				phit->SetActive(false);
				phit++;
			}
			if (!Side)
			{
				board[currPos.y][currPos.x] = 0;
				if (dame == false)
					board[masMousePos.y][masMousePos.x] = -1;
				else
					board[masMousePos.y][masMousePos.x] = -2;
				battlePos = Vector2i(0, 0);
				if (battle)
				{
					battlePos = masMousePos;
					if (!dame)
						board[(masMousePos.y + currPos.y) / 2][(masMousePos.x + currPos.x) / 2] = 0;
					else
					{
						offsetX = currPos.x - masMousePos.x;
						offsetY = currPos.y - masMousePos.y;
						if (offsetX > 0)offsetX = 1;
						else offsetX = -1;
						if (offsetY > 0)offsetY = 1;
						else offsetY = -1;
						for (enemyPos.x = masMousePos.x, enemyPos.y = masMousePos.y; board[enemyPos.y][enemyPos.x] != 1 && board[enemyPos.y][enemyPos.x] != 2; enemyPos.x += offsetX, enemyPos.y += offsetY) {};
						board[enemyPos.y][enemyPos.x] = 0;
					}
					for (int i = 0; i < AMM; i++)
					{
						if (field.GetChecker(i).GetActive())
						{
							if (!dame && field.GetChecker(i).CheckingForClick(113 * ((masMousePos.x + currPos.x) / 2 + 1), 113 * ((masMousePos.y + currPos.y + 1) / 2 + 1)))
							{
								field.GetChecker(i).SetActive(false);
								field.GetChecker(i).GetSprite().setColor(Color::Transparent);
							}
							else if (field.GetChecker(i).CheckingForClick(113 * (enemyPos.x + 1), 113 * (enemyPos.y + 1)))
							{
								field.GetChecker(i).SetActive(false);
								field.GetChecker(i).GetSprite().setColor(Color::Transparent);
							}
						}
					}
				}
			}
			else if (Side)
			{
				board[currPos.y][currPos.x] = 0;
				if (dame == false)
					board[masMousePos.y][masMousePos.x] = 1;
				else
					board[masMousePos.y][masMousePos.x] = 2;
				battlePos = Vector2i(0, 0);
				if (battle)
				{
					battlePos = masMousePos;
					if (!dame)
						board[(masMousePos.y + currPos.y) / 2][(masMousePos.x + currPos.x) / 2] = 0;
					else
					{
						offsetX = currPos.x - masMousePos.x;
						offsetY = currPos.y - masMousePos.y;
						if (offsetX > 0)offsetX = 1;
						else offsetX = -1;
						if (offsetY > 0)offsetY = 1;
						else offsetY = -1;
						for (enemyPos.x = masMousePos.x, enemyPos.y = masMousePos.y; board[enemyPos.y][enemyPos.x] != -1 && board[enemyPos.y][enemyPos.x] != -2; enemyPos.x += offsetX, enemyPos.y += offsetY);
						board[enemyPos.y][enemyPos.x] = 0;
					}
					for (int i = 0; i < AMM; i++)
					{
						if (field.GetChecker(i).GetActive())
						{
							if (!dame && field.GetChecker(i).CheckingForClick(113 * ((masMousePos.x + currPos.x) / 2 + 1), 113 * ((masMousePos.y + currPos.y + 1) / 2 + 1)))
							{
								field.GetChecker(i).SetActive(false);
								field.GetChecker(i).GetSprite().setColor(Color::Transparent);
							}
							else if (field.GetChecker(i).CheckingForClick(113 * (enemyPos.x + 1), 113 * (enemyPos.y + 1)))
							{
								field.GetChecker(i).SetActive(false);
								field.GetChecker(i).GetSprite().setColor(Color::Transparent);
							}
						}
					}
				}
			}
			Side = !Side;
			var = 0;
			break;
		}
		phit++;
	}
}

int MoveHints(Vector2i Pos, Vector2i Coord[15], bool Side, bool dame)
{
	int x;
	int y;
	int number = 0, k;
	if (dame)k = 8;
	else k = 1;
	for (int i = 0; i < 4; i++)
	{
		x = Pos.x;
		y = Pos.y;
		for (int j = 0; x < MAX && x >= 0 && y < MAX && y >= 0 && j < k; j++)
		{
			if (i == 0 && (Side == false || dame))
			{
				x = x + 1;
				y = y + 1;
			}
			else if (i == 1 && (Side == false || dame))
			{
				x = x - 1;
				y = y + 1;

			}
			else if (i == 2 && (Side == true || dame))
			{
				x = x + 1;
				y = y - 1;
			}
			else if (i == 3 && (Side == true || dame))
			{
				x = x - 1;
				y = y - 1;
			}
			if ((board[y][x] == 1 || board[y][x] == 2) && Side || (board[y][x] == -1 || board[y][x] == -2) && !Side)
			{
				break;
			}
			if (board[y][x] == 0 && x >= 0 && y >= 0 && x < 8 && y < 8)
			{
				Coord[number++] = Vector2i(x, y);
			}

			if (i == 0 && ((board[y][x] > 0 && board[y + 1][x + 1] > 0 && Side == false) || (board[y][x] < 0 && board[y + 1][x + 1] < 0 && Side == true)) && x + 1 < MAX && y + 1 < MAX)
			{
				break;
			}
			else if (i == 1 && ((board[y][x] > 0 && board[y + 1][x - 1] > 0 && Side == false) || (board[y][x] < 0 && board[y + 1][x - 1] < 0 && Side == true)) && x - 1 >= 0 && y + 1 < MAX)
			{
				break;
			}
			else if (i == 2 && ((board[y][x] > 0 && board[y - 1][x + 1] > 0 && Side == false) || (board[y][x] < 0 && board[y - 1][x + 1] < 0 && Side == true)) && x + 1 < MAX && y - 1 >= 0)
			{
				break;
			}
			else if (i == 3 && ((board[y][x] > 0 && board[y - 1][x - 1] > 0 && Side == false) || (board[y][x] < 0 && board[y - 1][x - 1] < 0 && Side == true)) && x - 1 >= 0 && y - 1 >= 0)
			{
				break;
			}
		}
	}
	return number;
}
bool CheckingEvent(Vector2i Pos, bool Side, bool dame)
{
	int x;
	int y;
	int k;
	if (dame)k = MAX;
	else k = 1;
	for (int i = 0; i < 4; i++)
	{
		x = Pos.x;
		y = Pos.y;
		for (int j = 0; x < MAX && x >= 0 && y < MAX && y >= 0 && j < k; j++)
		{
			if (i == 0)
			{
				x = x + 1;
				y = y + 1;
			}
			else if (i == 1)
			{
				x = x - 1;
				y = y + 1;

			}
			else if (i == 2)
			{
				x = x + 1;
				y = y - 1;
			}
			else if (i == 3)
			{
				x = x - 1;
				y = y - 1;
			}
			if ((board[y][x] == 1 || board[y][x] == 2) && Side || (board[y][x] == -1 || board[y][x] == -2) && !Side)
			{
				break;
			}
			if (i == 0 && ((board[y][x] > 0 && board[y + 1][x + 1] == 0 && Side == false) || (board[y][x] < 0 && board[y + 1][x + 1] == 0 && Side == true)) && x + 1 < MAX && y + 1 < MAX)
			{
				return false;
			}
			else if (i == 1 && ((board[y][x] > 0 && board[y + 1][x - 1] == 0 && Side == false) || (board[y][x] < 0 && board[y + 1][x - 1] == 0 && Side == true)) && x - 1 >= 0 && y + 1 < MAX)
			{
				return false;
			}
			else if (i == 2 && ((board[y][x] > 0 && board[y - 1][x + 1] == 0 && Side == false) || (board[y][x] < 0 && board[y - 1][x + 1] == 0 && Side == true)) && x + 1 < MAX && y - 1 >= 0)
			{
				return false;
			}
			else if (i == 3 && ((board[y][x] > 0 && board[y - 1][x - 1] == 0 && Side == false) || (board[y][x] < 0 && board[y - 1][x - 1] == 0 && Side == true)) && x - 1 >= 0 && y - 1 >= 0)
			{
				return false;
			}

			if (i == 0 && ((board[y][x] > 0 && board[y + 1][x + 1] > 0 && Side == false) || (board[y][x] < 0 && board[y + 1][x + 1] < 0 && Side == true)) && x + 1 < MAX && y + 1 < MAX)
			{
				break;
			}
			else if (i == 1 && ((board[y][x] > 0 && board[y + 1][x - 1] > 0 && Side == false) || (board[y][x] < 0 && board[y + 1][x - 1] < 0 && Side == true)) && x - 1 >= 0 && y + 1 < MAX)
			{
				break;
			}
			else if (i == 2 && ((board[y][x] > 0 && board[y - 1][x + 1] > 0 && Side == false) || (board[y][x] < 0 && board[y - 1][x + 1] < 0 && Side == true)) && x + 1 < MAX && y - 1 >= 0)
			{
				break;
			}
			else if (i == 3 && ((board[y][x] > 0 && board[y - 1][x - 1] > 0 && Side == false) || (board[y][x] < 0 && board[y - 1][x - 1] < 0 && Side == true)) && x - 1 >= 0 && y - 1 >= 0)
			{
				break;
			}
		}
	}
	return true;
}
int PlacingHints(Hint *p, Vector2i *moveCoord, int var)
{
	Hint *phit = p;
	int i;
	for (i = 0; i < var; i++)
	{
		if (moveCoord[i].x >= 0 && moveCoord[i].y >= 0 && (moveCoord[i].x + 1) * 113 >= 80 && (moveCoord[i].x + 1) * 113 <= 113 * 8 && (moveCoord[i].y + 1) * 113 >= 80 && (moveCoord[i].y + 1) * 113 <= 113 * 8)
		{
			phit->SetPosition((moveCoord[i].x + 1) * 113, (moveCoord[i].y + 1) * 113);
			phit->SetActive(true);
			phit++;
		}
	}
	return i;
}

Vector2i CheckingForWin(CheckerBoard& field)
{
	int player1 = 0;
	int player2 = 0;
	for (int i = 0; i < 24; i++)
	{
		if (!field.GetChecker(i).GetActive() && !field.GetChecker(i).GetPlayer())
		{
			player1++;
		}
		if (!field.GetChecker(i).GetActive() && field.GetChecker(i).GetPlayer())
		{
			player2++;
		}
	}
	if (player1 >= 12)
	{
		return Vector2i(1, 1);
	}
	else if (player2 >= 12)
	{
		return Vector2i(1, 0);
	}
	return Vector2i(0, 0);
}
bool CheckingPosHint(Hint *p)
{
	Hint *phint = p;
	for (int i = 0; i < numHint; i++)
	{
		if (phint->GetSprite().getGlobalBounds().contains(objMousePos.x, objMousePos.y) && phint->GetActive())
		{
			return true;
		}
		phint++;
	}
	return false;
}
void FormingField(CheckerBoard &field)
{
	int amm = 0;
	int X = 113, Y = 113;
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (board[i][j] > 0 || board[i][j] < 0)
			{
				field.GetChecker(amm).SetPosition(X, Y);
				if (board[i][j] == 2 || board[i][j] == -2)
				{
					field.GetChecker(amm).SetDame(true);
				}
				field.GetChecker(amm).CreatingChecker(board[i][j]);
				amm++;
			}
			X += 113;
		}
		X = 113;
		Y += 113;
	}
}
Vector2i MasCursorPos(Vector2f Pos)
{
	return Vector2i(Pos.x / 113 - 1, Pos.y / 113 - 1);
}

