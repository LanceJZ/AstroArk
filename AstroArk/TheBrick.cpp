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

void TheBrick::SetSounds(Sound hitSound, Sound destroySound)
{
	HitSound = hitSound;
	DestroySound = destroySound;
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

	LeftSide->Radius = 4.50f;
	RightSide->Radius = 4.50f;
	Radius = 6.50f;
	LeftSide->X(-10.750f);
	RightSide->X(10.750f);
	LeftSide->SetParent(*this);
	RightSide->SetParent(*this);
	LeftSide->ShowCollision = true;
	RightSide->ShowCollision = true;
	ShowCollision = true;
	ModelColor = Color ( 130.0f, 20.0f, 255.0f, 255.0f );

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
	Model3D::Spawn(position);

}

void TheBrick::Spawn()
{
	Entity::Spawn();
	LeftSide->Spawn();
	RightSide->Spawn();
}

void TheBrick::Destroy()
{
	Entity::Destroy();

	LeftSide->Destroy();
	RightSide->Destroy();
}

void TheBrick::Hit(Vector3 position, Vector3 velocity)
{

	if (EM.TimerElapsed(HitTimerID))
	{
		if (!Player->GameOver) PlaySound(DestroySound);

		Destroy();
		return;
	}

	EM.ResetTimer(HitTimerID);
	//Velocity = GetReflectionVelocity(position, velocity, 100.0f, 0.5f);

}

void TheBrick::PlayerHit()
{
	PlaySound(HitSound);

	if (EM.TimerElapsed(HitTimerID)) Health--;
;
	EM.ResetTimer(HitTimerID);

	if (Health <= 0)
	{
		Score.AddToScore(Points);

		if (!Player->GameOver) PlaySound(DestroySound);

		Destroy();
		return;
	}
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
			PlayerHit();
			shot->Hit(Position, { 0.0f });
		}
	}

	if (Player->Enabled)
	{
		if (Player->Shield->Enabled)
		{
			if (CirclesIntersect(*Player->Shield))
			{
				Player->ShieldHit(Position, { 0.0f });
			}
		}

		if (CirclesIntersect(*Player))
		{
			PlayerHit();
			{
				Player->Hit(Position, { 0.0f });
			}
		}
	}
}
