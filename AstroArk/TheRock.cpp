#include "TheRock.h"

TheRock::TheRock()
{
}

TheRock::~TheRock()
{
}

void TheRock::SetPlayer(ThePlayer* player)
{
	Player = player;
}

void TheRock::SetExplodeSound(Sound sound)
{
	ExplodeSound = sound;
	SetSoundVolume(ExplodeSound, 0.333f);
}

bool TheRock::Initialize()
{
	LineModel::Initialize();

	return false;
}

bool TheRock::BeginRun()
{
	LineModel::BeginRun();

	return false;
}

void TheRock::Update(float deltaTime)
{
	LineModel::Update(deltaTime);

	CheckCollisions();
}

void TheRock::FixedUpdate(float deltaTime)
{
	LineModel::FixedUpdate(deltaTime);

	CheckScreenEdge();
}

void TheRock::AlwaysUpdate(float deltaTime)
{
	LineModel::AlwaysUpdate(deltaTime);
}

void TheRock::Draw3D()
{
	LineModel::Draw3D();
}

void TheRock::Spawn(Vector3 position, RockSize size)
{
	Entity::Spawn(position);

	float magnitude = 0;
	float angle = M.GetRandomRadian();
	float maxVS = 0;

	TheRock::Size = size;
	float scale = 25;
	float change = 0;

	switch (size)
	{
	case Small:
		change = 4.5f;
		Scale = scale / change;
		maxVS = 3;
		magnitude = M.GetRandomFloat(52.3f, 74.1f);
		Velocity = GetVelocityFromAngleZ(angle, magnitude);
		break;
	case Medium:
		change = 2.75f;
		Scale =  scale / change;
		maxVS = 2;
		magnitude = M.GetRandomFloat(43.2f, 63.1f);
		Velocity = GetVelocityFromAngleZ(angle, magnitude);
		break;
	case MediumLarge:
		change = 1.85f;
		Scale =  scale / change;
		maxVS = 2;
		magnitude = M.GetRandomFloat(36.1f, 56.1f);
		Velocity = GetVelocityFromAngleZ(angle, magnitude);
		break;
	case Large:
		Y(M.GetRandomFloat(-WindowHalfHeight, WindowHalfHeight));
		Scale = scale;
		maxVS = 1;

		magnitude = M.GetRandomFloat(20.35f, 40.1f);
		Velocity = GetVelocityFromAngleZ(angle, magnitude);

		if (Velocity.x > 0)
		{
			X(-WindowHalfWidth);
		}
		else
		{
			X(WindowHalfWidth);
		}

		break;
	}

	float rVel = M.GetRandomFloat(-maxVS, maxVS);

	if (rVel < 0.1)
	{
		rVel++;
	}
	else if (rVel > -0.1)
	{
		rVel--;
	}

	RotationVelocityZ = rVel;
}

void TheRock::Destroy()
{
	LineModel::Destroy();

}

void TheRock::Hit()
{
	LineModel::Hit();

	if (!Player->GameOver) PlaySound(ExplodeSound);
}

void TheRock::Hit(Vector3 position, Vector3 velocity)
{
	Velocity = GetReflectionVelocity(position, velocity, 100.0f);
}

void TheRock::Reset()
{
	LineModel::Reset();

	Enabled = false;
}

bool TheRock::CheckCollisions()
{
	if (Player->Enabled && CirclesIntersect(*Player))
	{
		//if (!Player->Shield->Enabled) Hit();

		if (Player->Shield->Enabled)
		{
			Player->ShieldHit(Position, { 0.0f });
			return false;
		}

		Hit();
		Player->BeenHit = true;
		SetScore();

		return true;
	}

	for (const auto& shot : Player->Shots)
	{
		if (shot->Enabled && CirclesIntersect(*shot))
		{
			shot->Hit(Position, { 0.0f });
			Hit();
			SetScore();
			return true;
		}
	}

	return false;
}

void TheRock::SetScore()
{
	switch (Size)
	{
	case Large:
		Score.AddToScore(20);
		break;
	case Medium:
		Score.AddToScore(50);
		break;
	case Small:
		Score.AddToScore(100);
		break;
	}
}
