#pragma once

#include "ConsoleMario.h"
#include <vector>
#include "PlayerInput.h"

class GameInstance
{
public:
	GameInstance();

	static GameInstance* GetInstance();

	void RunGame();

	void ReserveStartLevel(const std::string& _mapFileName, int _entry);

	void AddGameScore();

	int GetGameScore() const;

	PlayerInput* GetInput() const;

public:
	const std::string MapFileName = "map";
	static const int ScreenXCount = 30;
	static const int ScreenYCount = 15;
	const float Gravity = -9.0f;


private:
	void InitializeBeforeGameplay();

	void LobbyTick();
	void GameplayTick();
	void GameClearTick();
	void GameOverTick();
	void OnEndGame();

	void StartLevel(const std::string& _mapFileName, int _entry);

	void AttemptDestroyMarked();
	void AttemptStartReservedLevel();

private:
	enum class EGameState
	{
		Lobby, Game, GameClear, GameOver, End
	};

	const int TargetFPS = 30;

	static GameInstance* Instance;

	bool bReserveStartLevel = false;
	std::string ReservedLevelName = "";
	int ReservedLevelEntry = 0;

	float DeltaTime;
	float ElapsedGameTime;

	EGameState CurrentGameState = EGameState::Lobby;
	bool bEscape = false;
	int GameScore;

	class Map* CurrentMap;
	std::vector < class PhysicsBody*>* PhysicsBodies;
	std::vector < class StaticObject*>* StaticObjects;
	class Player* ControlledPlayer;

	class ConsoleRenderer* Renderer;
	PlayerInput* Input;

};

