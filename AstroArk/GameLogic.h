#pragma once
#include "Globals.h"
#include "ThePlayer.h"
#include "EnemyControl.h"

enum GameState
{
	Ended,
	InPlay,
	Bonus,
	BonusPoints,
	BonusCity,
	BonusCityAwarded,
	Pause,
	HighScores,
	MainMenu,
	Attract
};

class GameLogic : public Common
{
public:
	GameLogic();
	virtual ~GameLogic();

	bool PlayBackgroundMusic = true;
	GameState State = MainMenu;

	void SetPlayer(ThePlayer* player);
	void SetEnemies(EnemyControl* enemies);

	bool Initialize();
	bool BeginRun();
	bool Load();

	void FixedUpdate();
	void Input();
	void NewGame();

private:
	bool GameEnded = false;
	Vector2 AdjustedFieldSize = {};

	ThePlayer* Player = {};
	EnemyControl* Enemies = {};

	void GamePlay();
	void IsOver();
};