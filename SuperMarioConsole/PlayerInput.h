#pragma once

#include "ConsoleMario.h"

class PlayerInput
{
	enum class EKeyCode : int
	{
		None = 0,
		A = 97, D = 100, W = 119, S = 115,
		Enter = 13, ESC = 27
	};

public:
	PlayerInput();

	void Update();

	void Reset();

public:
	int AnyKey() const
	{
		return this->bAnyKey;
	}

	int GetHorizontal() const
	{
		return this->Horizontal;
	}
	bool GetJump() const
	{
		return this->bJump;
	}
	bool GetEnter() const
	{
		return this->bEnter;
	}
	bool GetExit() const
	{
		return this->bExit;
	}
	bool GetDown() const
	{
		return this->bDown;
	}

private:
	bool bAnyKey;

	int Horizontal;
	bool bJump;
	bool bEnter;
	bool bExit;
	bool bDown;

};
