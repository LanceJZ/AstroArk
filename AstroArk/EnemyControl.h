#pragma once
#include "Globals.h"
#include "TheUFO.h"
#include "TheRock.h"

class EnemyControl : public Common
{
public:
	EnemyControl();
	virtual ~EnemyControl();

	std::vector<TheUFO*> UFOs = {};
	std::vector<TheRock*> Rocks = {};

	void SetPlayer(ThePlayer* player);
	void SetUFOModel(LineModelPoints model);
	void SetShotModel(LineModelPoints model);
	void SetRockModels(LineModelPoints rockModels[4]);

	void SetUFOSounds(Sound explode, Sound fire, Sound active);
	void SetRockExplodeSound(Sound sound);

	bool Initialize();
	bool BeginRun();

	void Update();

	void NextWave();
	void NewGame();
	void Reset();

private:
	bool NoMoreRocks = false;

	size_t UFOSpawnTimerID = 0;
	unsigned int RockCount = 0;
	unsigned int WaveNumber = 0;
	unsigned int StartRockCount = 1;
	unsigned int RockSpawnCount = 0;

	LineModelPoints UFOModel = {};
	LineModelPoints ShotModel = {};

	Sound UFOExplodeSound = {};
	Sound UFOFireSound = {};
	Sound UFOActiveSound = {};
	Sound RockExplodeSound = {};

	ThePlayer *Player = nullptr;
	LineModelPoints RockModels[4] = {};

	void SpawnUFO();
	void SpawnRocks(Vector3 position, int count, TheRock::RockSize size);
	void CheckRockCollisions();

	bool CheckUFOCollisions(TheRock* rock);
};