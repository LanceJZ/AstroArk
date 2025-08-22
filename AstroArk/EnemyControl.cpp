#include "EnemyControl.h"

EnemyControl::EnemyControl()
{
	UFOSpawnTimerID = EM.AddTimer();
}

EnemyControl::~EnemyControl()
{
}

void EnemyControl::SetPlayer(ThePlayer* player)
{
	Player = player;
}

void EnemyControl::SetUFOModel(LineModelPoints model)
{
	UFOModel = model;
}

void EnemyControl::SetShotModel(LineModelPoints model)
{
	ShotModel = model;
}

void EnemyControl::SetUFOSounds(Sound explode, Sound fire, Sound active)
{
	UFOExplodeSound = explode;
	UFOFireSound = fire;
	UFOActiveSound = active;
}

bool EnemyControl::Initialize()
{
	Common::Initialize();


	return false;
}

bool EnemyControl::BeginRun()
{
	Common::BeginRun();

	Reset();

	return false;
}

void EnemyControl::Update()
{
	Common::Update();

	if (EM.TimerElapsed(UFOSpawnTimerID)) SpawnUFO();

}

void EnemyControl::NewGame()
{
	Reset();

}


void EnemyControl::SpawnUFO()
{
	EM.ResetTimer(UFOSpawnTimerID, 20.0f);
	bool spawnUFO = true;
	size_t ufoNumber = UFOs.size();

	for (size_t check = 0; check < ufoNumber; check++)
	{
		if (!UFOs.at(check)->Enabled)
		{
			spawnUFO = false;
			ufoNumber = check;
			break;
		}
	}

	if (spawnUFO)
	{
		UFOs.push_back(DBG_NEW TheUFO());
		EM.AddLineModel(UFOs.back(), UFOModel);
		UFOs.back()->SetShotModel(ShotModel);
		UFOs.back()->SetSounds(UFOExplodeSound, UFOFireSound, UFOActiveSound);
		UFOs.back()->SetPlayer(Player);
		UFOs.back()->BeginRun();

	}

	UFOs.at(ufoNumber)->Spawn();
}

void EnemyControl::Reset()
{
	for (const auto& ufo : UFOs)
	{
		ufo->Reset();
	}

	EM.ResetTimer(UFOSpawnTimerID, 2.0f);
}
