#include "MainHeader.h"

int CheckerBattle(Vector2i, Vector2i[15], bool, bool);
int MoveHints(Vector2i, Vector2i[15], bool, bool);
void CheckerMove(Hint *, int&, bool &, bool, CheckerBoard&, bool);
bool CheckingEvent(Vector2i, bool, bool);
int PlacingHints(Hint *, Vector2i *, int);
Vector2i CheckingForWin(CheckerBoard&);
bool CheckingPosHint(Hint *);
void FormingField(CheckerBoard &);
Vector2i MasCursorPos(Vector2f);

