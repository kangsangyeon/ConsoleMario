#include "PlayerInput.h"

#include <conio.h>

PlayerInput::PlayerInput()
{
	Reset();
}

void PlayerInput::Update()
{
	Reset();

	if (_kbhit())
	{
		bAnyKey = true;

		int _input = _getch();

		Horizontal = _input == 'a' || _input == 'A' ? -1
			: _input == 'd' || _input == 'D' ? 1
			: 0;

		bJump = _input == 'w' || _input == 'W';
		bEnter = _input == 13;
		bExit = _input == 27;
		bDown = _input == 's' || _input == 'S';
	}

}

void PlayerInput::Reset()
{
	bAnyKey = false;

	Horizontal = 0;
	bJump = false;
	bEnter = false;
	bExit = false;
}
