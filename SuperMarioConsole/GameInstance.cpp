#include "GameInstance.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <chrono>

#include "MapFileReader.h"
#include "ConsoleRenderer.h"
#include "PhysicsBody.h"
#include "StaticObject.h"
#include "Player.h"
#include "Vector2D.h"

GameInstance* GameInstance::Instance = nullptr;

GameInstance::GameInstance()
{
	Instance = this;

	bEscape = false;
	CurrentGameState = EGameState::Lobby;

	DeltaTime = 0.0f;
	ElapsedGameTime = 0.0f;
	CurrentMap = nullptr;
	PhysicsBodies = nullptr;
	ControlledPlayer = nullptr;
	Renderer = nullptr;

	Input = new PlayerInput();
}

GameInstance* GameInstance::GetInstance()
{
	return Instance;
}

void GameInstance::InitializeBeforeGameplay()
{
	GameScore = 0;
	DeltaTime = 0.0f;
	ElapsedGameTime = 0.0f;

	if (Renderer != nullptr)
	{
		delete Renderer;
		Renderer = nullptr;
	}
	Renderer = new ConsoleRenderer();
}

void GameInstance::StartLevel(const std::string& _mapFileName, int _entry)
{
	if (CurrentMap != nullptr)
	{
		delete CurrentMap;
		CurrentMap = nullptr;
	}
	if (PhysicsBodies != nullptr)
	{
		delete PhysicsBodies;
		PhysicsBodies = nullptr;
	}
	if (ControlledPlayer != nullptr)
	{
		delete ControlledPlayer;
		ControlledPlayer = nullptr;
	}
	if (StaticObjects != nullptr)
	{
		delete StaticObjects;
		StaticObjects = nullptr;
	}

	MapFileReader::ReadFromFile(MapFileName, _entry, &CurrentMap, &ControlledPlayer, &PhysicsBodies, &StaticObjects);

	ControlledPlayer->BindPlayerInput(Input);
}

void GameInstance::ReserveStartLevel(const std::string& _mapFileName, int _entry)
{
	bReserveStartLevel = true;
	ReservedLevelName = _mapFileName;
	ReservedLevelEntry = _entry;
}

void GameInstance::LobbyTick()
{
	Input->Update();

	std::cout << "WELCOME TO CONSOLE MARIO" << std::endl;
	std::cout << "PRESS ENTER TO START, ESC TO EXIT" << std::endl;

	if (Input->GetEnter() == true)
	{
		InitializeBeforeGameplay();
		StartLevel(MapFileName, 0);
		CurrentGameState = EGameState::Game;
	}
	else if (Input->GetExit() == true)
	{
		bEscape = true;
	}
}

void GameInstance::GameplayTick()
{
	Input->Update();

	if (ControlledPlayer->GetIsClear())
	{
		CurrentGameState = EGameState::GameClear;
		return;
	}

	AttemptStartReservedLevel();

	std::cout << StringFormat("Elapsed GameTime: %f", ElapsedGameTime) << std::endl;
	std::cout << StringFormat("GameScore: %d", GetGameScore()) << std::endl;

	std::cout << Input->GetHorizontal() << "\t" << Input->GetJump() << "\t" << ControlledPlayer->GetPosition().ToString() << std::endl;

	for (int _i = 0; _i < PhysicsBodies->size(); _i++)
	{
		(*PhysicsBodies)[_i]->UpdateMove(*CurrentMap, DeltaTime, Gravity);
	}

	if (ControlledPlayer->GetIsDead())
	{
		CurrentGameState = EGameState::GameOver;
	}

	AttemptDestroyMarked();

	Renderer->Render(CurrentMap, ControlledPlayer->GetPosition().GetRounded());

	// -----------------------------------------------------------------------------------------

	if (Input->GetExit() == true)
	{
		CurrentGameState = EGameState::Lobby;
	}
}

void GameInstance::GameClearTick()
{
	Input->Update();

	std::cout << "congratulation!" << std::endl;
	std::cout << "you clear this level" << std::endl;
	std::cout << std::endl;
	std::cout << "enter to retry" << std::endl;
	std::cout << "esc to exit" << std::endl;

	if (Input->GetEnter())
	{
		CurrentGameState = EGameState::Lobby;
	}
	else if (Input->GetExit())
	{
		bEscape = true;
	}
}

void GameInstance::GameOverTick()
{
	Input->Update();

	std::cout << "game over. " << std::endl;
	std::cout << "enter to retry" << std::endl;
	std::cout << "esc to exit" << std::endl;

	if (Input->GetEnter())
	{
		CurrentGameState = EGameState::Lobby;
	}
	else if (Input->GetExit())
	{
		bEscape = true;
	}

}

void GameInstance::OnEndGame()
{
	std::cout << "Thanks for playing." << std::endl;
	std::cout << std::endl;
}

/// <summary>
///  파괴 예약이 되어있던 오브젝트들을 파괴합니다. 파괴 예약이 되어있는 오브젝트가 전혀 없다면 아무 일도 일어나지 않습니다.
/// </summary>
void GameInstance::AttemptDestroyMarked()
{
	for (int _i = 0; _i < PhysicsBodies->size(); _i++)
	{
		if (PhysicsBodies->at(_i)->GetWillDestroy() == true)
		{
			PhysicsBodies->erase(PhysicsBodies->begin() + _i);
			_i--;
		}

	}

	for (int _i = 0; _i < StaticObjects->size(); _i++)
	{
		if (StaticObjects->at(_i)->GetWillDestroy() == true)
		{
			PhysicsBodies->erase(PhysicsBodies->begin() + _i);
			_i--;
		}
	}
}

/// <summary>
/// 예약된 레벨이 있다면 그 레벨을 시작합니다. 없다면 아무일도 일어나지 않습니다.
/// </summary>
void GameInstance::AttemptStartReservedLevel()
{
	if (bReserveStartLevel)
	{
		bReserveStartLevel = false;

		StartLevel(ReservedLevelName, ReservedLevelEntry);
		ReservedLevelName = "";
		ReservedLevelEntry = 0;
	}
}

void GameInstance::RunGame()
{
	const DWORD SleepTimeMillis = 1000.0 / TargetFPS;

	const auto _startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	auto _latestTime = _startTime;

	while (bEscape == false)
	{
		// 시간 정보를 화면 왼쪽 위에 표시한다.
		auto _currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		ElapsedGameTime = (_currentTime - _startTime) / 1000.0f;
		DeltaTime = (_currentTime - _latestTime) / 1000.0f;
		_latestTime = _currentTime;

		std::cout << DeltaTime << " -> " << SleepTimeMillis * 0.001 << std::endl;

		switch (CurrentGameState)
		{
		case EGameState::Lobby:
			LobbyTick();
			break;
		case EGameState::Game:
			GameplayTick();
			break;
		case EGameState::GameOver:
			GameOverTick();
			break;
		case EGameState::GameClear:
			GameClearTick();
			break;
		case EGameState::End:
			bEscape = true;
			break;
		}

		Sleep(SleepTimeMillis);

		system("cls");
	}

	system("cls");
	OnEndGame();
}

void GameInstance::AddGameScore()
{
	GameScore++;
}

int GameInstance::GetGameScore() const
{
	return GameScore;
}

PlayerInput* GameInstance::GetInput() const
{
	return this->Input;
}

