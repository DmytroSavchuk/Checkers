#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "MyCursor.h"
#include "CheckerBoard.h"
#include "Hint.h"

#define MAX 8
#define AMM 24

using namespace sf;
using namespace std;

extern Vector2i mousePos, masMousePos, currPos, battlePos, enemyPos, winCondition;
extern Vector2f objMousePos;
extern int numHint;

extern int board[MAX][MAX];
