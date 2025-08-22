#include "TheUFO.h"

TheUFO::TheUFO()
{
	VectorChangeTimerID = EM.AddTimer(5.5f);
	FireShotTimerID = EM.AddTimer(0.5f);
}

TheUFO::~TheUFO()
{
}

void TheUFO::SetSounds(Sound explode, Sound fire, Sound active)
{
	ExplodeSound = explode;
	FireSound = fire;
	ActiveSound = active;
}

bool TheUFO::Initialize()
{
	Enemy::Initialize();

	return false;
}

bool TheUFO::BeginRun()
{
	Enemy::BeginRun();

	SetSoundVolume(ActiveSound, 0.5f);

	return false;
}

void TheUFO::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	CheckScreenEdge();

	if (EM.TimerElapsed(VectorChangeTimerID)) ChangeVector();

	if (EM.TimerElapsed(FireShotTimerID)) FireShot();

	if (!IsSoundPlaying(ActiveSound) && !Player->GameOver) PlaySound(ActiveSound);
}

void TheUFO::AlwaysUpdate(float deltaTime)
{
	Enemy::AlwaysUpdate(deltaTime);

	CheckShotsHitPlayer();
}

void TheUFO::FixedUpdate(float deltaTime)
{
	Enemy::FixedUpdate(deltaTime);
}

void TheUFO::Draw3D()
{
	Enemy::Draw3D();
}

void TheUFO::Spawn()
{
	Enemy::Spawn();

	Vector3 position = { 0.0f, 0.0f, 0.0f };
	int height = (int)(WindowHalfHeight * 0.9f);
	position.y = (float)GetRandomValue(-height, height);

	MaxSpeed = 128.666f;

	if (GetRandomValue(1, 10) < 5)
	{
		position.x = WindowHalfWidth;
		Velocity.x = -MaxSpeed;
	}
	else
	{
		position.x = -WindowHalfWidth;
		Velocity.x = MaxSpeed;
	}


	Enemy::Spawn(position);
}

void TheUFO::Destroy()
{
	Enemy::Destroy();

	PlaySound(ExplodeSound);
}

void TheUFO::FireShot()
{
	if (Player->GameOver) return;

	PlaySound(FireSound);

	float angle = 0;
	float shotSpeed = 325;
	bool shootRocks = false;
	EM.ResetTimer(FireShotTimerID, 3.5f);

	angle = M.GetRandomRadian();

	//if (GetRandomValue(1, 10) < 3)
	//{
	//	angle = M.GetRandomRadian();
	//}
	//else
	//{
	//	angle = AimedShot();
	//}

	bool spawnNew = true;
	size_t spawnNumber = Shots.size();

	for (size_t check = 0; check < spawnNumber; check++)
	{
		if (!Shots[check]->Enabled)
		{
			spawnNew = false;
			spawnNumber = check;
			break;
		}
	}

	if (spawnNew)
	{
		Shots.push_back(DBG_NEW Shot());
		EM.AddLineModel(Shots.back(), ShotModel);
		Shots.back()->Initialize();
		Shots.back()->BeginRun();
	}

	if (!Player->GameOver) PlaySound(FireSound);

	Vector3 position = Vector3Add(GetVelocityFromAngleZ(Radius), Position);
	Shots[spawnNumber]->Spawn(position, GetVelocityFromAngleZ(angle, shotSpeed), 2.5f);
}

void TheUFO::ChangeVector()
{
	float vectorTimer = M.GetRandomFloat(3.1f - (WaveNumber * 0.1f), 7.5f);

	if (vectorTimer < 0.25f) vectorTimer = 0.25f;

	EM.ResetTimer(VectorChangeTimerID, vectorTimer);

	if (GetRandomValue(1, 10) > 2)
	{
		if ((int)Velocity.y == 0)
		{
			if (GetRandomValue(1, 10) < 5)
			{
				Velocity.y = MaxSpeed;
			}
			else
			{
				Velocity.y = -MaxSpeed;
			}
		}
		else
		{
			if (Position.y < WindowHalfHeight - (Radius * 3) &&
				Position.y > -WindowHalfHeight - (Radius * 3))
			{
				Velocity.y = 0;
			}
		}
	}
}

bool TheUFO::CheckCollisions()
{
	Enemy::CheckCollisions();

	return false;
}

float TheUFO::AimedShot()
{

	return 0.0f;
}
