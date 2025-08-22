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

void EnemyControl::SetRockModels(LineModelPoints rockModels[4])
{
	for (int i = 0; i < 4; i++)
	{
		RockModels[i] = rockModels[i];
	}
}

void EnemyControl::SetUFOSounds(Sound explode, Sound fire, Sound active)
{
	UFOExplodeSound = explode;
	UFOFireSound = fire;
	UFOActiveSound = active;
}

void EnemyControl::SetRockExplodeSound(Sound sound)
{
	RockExplodeSound = sound;
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

	CheckRockCollisions();
}

void EnemyControl::NextWave()
{
	WaveNumber++;

	SpawnRocks(Vector3(0.0f, 0.0f, 0.0f), RockSpawnCount, TheRock::Large);
}

void EnemyControl::NewGame()
{
	Reset();
	NextWave();
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

void EnemyControl::SpawnRocks(Vector3 position, int count, TheRock::RockSize size)
{
	for (int rock = 0; rock < count; rock++)
	{
		bool spawnNewRock = true;
		size_t rockNumber = Rocks.size();

		for (size_t check = 0; check < rockNumber; check++)
		{
			if (!Rocks.at(check)->Enabled)
			{
				spawnNewRock = false;
				rockNumber = check;
				break;
			}
		}

		if (spawnNewRock)
		{
			size_t rockType = GetRandomValue(0, 3);
			Rocks.push_back(DBG_NEW TheRock());
			EM.AddLineModel(Rocks.back(), (RockModels[rockType]));
			Rocks.back()->SetPlayer(Player);
			Rocks.back()->SetExplodeSound(RockExplodeSound);
			Rocks.back()->BeginRun();

			for (const auto& ufo : UFOs)
			{
				//ufo->Rocks.push_back(Rocks.back());
			}
		}

		Rocks.at(rockNumber)->Spawn(position, size);
	}
}

void EnemyControl::CheckRockCollisions()
{
	bool ufoHitRock = false;
	bool enemyHitRock = false;
	NoMoreRocks = true;
	RockCount = 0;

	for (int i = 0; i < Rocks.size(); i++)
	{
		if (Rocks.at(i)->Enabled)
		{
			NoMoreRocks = false;
			RockCount++;

			if (CheckUFOCollisions(Rocks.at(i))) ufoHitRock = true;

			if (Rocks.at(i)->GetBeenHit())
			{
				if (!Player->GameOver)
				{
					int chance = 30;

					chance -= (int)((WaveNumber + 1) * 3.5f);

					if (chance < 1) chance = 1;

				}

				Rocks.at(i)->Destroy();
				Particles.SpawnLineDots(Rocks.at(i)->Position,
					Vector3Multiply(Rocks.at(i)->Velocity, { 0.25f, 0.25f }),
					Rocks.at(i)->Radius * 0.25f, 15.0f, 15, 1.5f, WHITE);

				int count = 0;

				int max = (int)(WaveNumber * 0.5f) + 5;

				if (ufoHitRock) count = GetRandomValue(4, max);
				else if (enemyHitRock) count = GetRandomValue(3, max);
				else count = GetRandomValue(1, 4);

				if (Rocks.at(i)->Size == TheRock::Large)
				{
					SpawnRocks(Rocks.at(i)->Position, count, TheRock::MediumLarge);
					continue;
				}
				else if (Rocks.at(i)->Size == TheRock::MediumLarge)
				{
					SpawnRocks(Rocks.at(i)->Position, count, TheRock::Medium);
					continue;
				}
				else if (Rocks.at(i)->Size == TheRock::Medium)
				{
					SpawnRocks(Rocks.at(i)->Position, count, TheRock::Small);
					continue;
				}
			}
		}
	}
}

void EnemyControl::Reset()
{
	WaveNumber = 0;
	RockSpawnCount = StartRockCount;

	for (const auto& ufo : UFOs)
	{
		ufo->Reset();
	}

	for (const auto& rock : Rocks)
	{
		rock->Reset();
	}

	EM.ResetTimer(UFOSpawnTimerID, 2.0f);
}

bool EnemyControl::CheckUFOCollisions(TheRock* rock)
{
	bool ufoHitRock = false;

	for (const auto& ufo : UFOs)
	{
		if (!ufo->Enabled) continue;

		//if (ufo->CheckRockCollisions(rock)) ufoHitRock = true;

		if (rock->Size == TheRock::Small) continue;

		if (ufo->CirclesIntersect(*rock))
		{
			ufo->Destroy();
			rock->Hit();
		}

		for (const auto& shot : ufo->Shots)
		{
			if (!shot->Enabled) continue;

			if (shot->CirclesIntersect(*rock))
			{
				shot->Destroy();
				rock->Hit();
			}
		}
	}

	return ufoHitRock;
}
