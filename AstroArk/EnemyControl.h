#pragma once
#include "Globals.h"
#include "TheUFO.h"

class EnemyControl : public Common
{
public:
	EnemyControl();
	virtual ~EnemyControl();

	std::vector<TheUFO*> UFOs = {};

	void SetPlayer(ThePlayer* player);
	void SetUFOModel(LineModelPoints model);
	void SetShotModel(LineModelPoints model);

	void SetUFOSounds(Sound explode, Sound fire, Sound active);

	bool Initialize();
	bool BeginRun();

	void Update();

	void NewGame();

private:
	size_t UFOSpawnTimerID = 0;

	LineModelPoints UFOModel = {};
	LineModelPoints ShotModel = {};

	Sound UFOExplodeSound;
	Sound UFOFireSound;
	Sound UFOActiveSound;

	ThePlayer *Player = nullptr;

	void SpawnUFO();
	void Reset();
};