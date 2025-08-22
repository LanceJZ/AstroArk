#pragma once
#include "Globals.h"
#include "ThePlayer.h"
#include "EnemyControl.h"
#include "TheBrickManager.h"

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
	void SetBrickManager(TheBrickManager* brickManager);

	bool Initialize();
	bool BeginRun();
	bool Load();

	void FixedUpdate();
	void Input();
	void NewGame();

private:
	bool GameEnded = false;
	Vector2 AdjustedFieldSize = {};

	Entity* PlayerClear = {};

	ThePlayer* Player = {};
	EnemyControl* Enemies = {};
	TheBrickManager* BrickManager = {};

	std::vector <LineModel*> PlayerShipModels;

	bool CheckPlayerClear();

	void PlayerShipDisplay();
	void AddPlayerShipModels(int number);
	void GamePlay();
	void CheckUFOBrickCollusions();
	void CheckRockCollusions();
	void IsOver();
	void InMainMenu();
	void IsPaused();
};