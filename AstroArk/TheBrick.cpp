#include "TheBrick.h"

TheBrick::TheBrick()
{
	EM.AddEntity(LeftSide = DBG_NEW Entity());
	EM.AddEntity(RightSide = DBG_NEW Entity());

	HitTimerID = EM.AddTimer(0.1f);
}

TheBrick::~TheBrick()
{
}

void TheBrick::SetPlayerReference(ThePlayer* player)
{
	Player = player;
}

bool TheBrick::Initialize()
{
	Model3D::Initialize();

	LeftSide->Initialize();
	RightSide->Initialize();

	return true;
}

bool TheBrick::BeginRun()
{
	Model3D::BeginRun();

	LeftSide->Radius = 6.50f;
	RightSide->Radius = 6.50f;
	Radius = 6.50f;
	LeftSide->X(-8.50f);
	RightSide->X(8.50f);
	LeftSide->SetParent(*this);
	RightSide->SetParent(*this);

	return true;
}

void TheBrick::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	CheckCollision();
}

void TheBrick::FixedUpdate(float deltaTime)
{
	Model3D::FixedUpdate(deltaTime);

	CheckScreenEdge();
}

void TheBrick::AlwaysUpdate(float deltaTime)
{
	Model3D::AlwaysUpdate(deltaTime);
}

void TheBrick::Draw3D()
{
	Model3D::Draw3D();
}

void TheBrick::Spawn(Vector3 position)
{
	Entity::Spawn(position);

}

void TheBrick::Destroy()
{
	Entity::Destroy();

}

void TheBrick::Hit(Vector3 position, Vector3 velocity)
{
	if (EM.TimerElapsed(HitTimerID)) Health--;
;
	EM.ResetTimer(HitTimerID);

	if (Health <= 0)
	{
		Score.AddToScore(Points);
		Destroy();
		return;
	}

	//Velocity = GetReflectionVelocity(position, velocity, 100.0f, 0.5f);

}

void TheBrick::CheckCollision()
{
	for (const auto& shot : Player->Shots)
	{
		if (!shot->Enabled) continue;

		if (CirclesIntersect(*shot) ||
			LeftSide->CirclesIntersect(*shot) ||
			RightSide->CirclesIntersect(*shot))
		{
			Hit(shot->Position, shot->Velocity);
			shot->Hit(Position, { 0.0f });
		}
	}

	if (Player->Enabled)
	{
		if (CirclesIntersect(*Player))
		{
			Hit(Player->Position, Player->Velocity);
			Player->Hit(Position, Player->Velocity);
		}
	}

}
