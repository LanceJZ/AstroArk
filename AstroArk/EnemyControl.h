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

	bool Initialize();
	bool BeginRun();

	void Update();

	void NewGame();

private:
	size_t UFOSpawnTimerID = 0;

	LineModelPoints UFOModel = {};
	LineModelPoints ShotModel = {};

	ThePlayer *Player = nullptr;

	void SpawnUFO();
	void Reset();
};