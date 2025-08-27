#include "Shot.h"

Shot::Shot()
{
	LifeTimerID = EM.AddTimer();
}

Shot::~Shot()
{
}

bool Shot::Initialize()
{
	LineModel::Initialize();

	return false;
}

bool Shot::BeginRun()
{
	Enabled = false;

	return false;
}

void Shot::Update(float deltaTime)
{
	LineModel::Update(deltaTime);

	if (EM.TimerElapsed(LifeTimerID)) Destroy();

}

void Shot::FixedUpdate(float fixedDeltaTime)
{
	LineModel::FixedUpdate(fixedDeltaTime);

	CheckScreenEdge();
}

void Shot::Draw3D()
{
	LineModel::Draw3D();
}

void Shot::Hit(Vector3 position, Vector3 velocity)
{
	Position = Vector3Add(Position,
		Vector3Multiply(Vector3Multiply(Velocity, { -1.0f }), { 0.1f }));

	Velocity = GetReflectionVelocity(position, velocity, 50.0f, 1.0f, 1.0f);
}

void Shot::Spawn(Vector3 position)
{
	Entity::Spawn(position);
}

void Shot::Spawn(Vector3 position, Vector3 velocity)
{
	Spawn(position);
	Velocity = velocity;
}

void Shot::Spawn(Vector3 position, Vector3 velocity, float lifetime)
{
	EM.ResetTimer(LifeTimerID, lifetime);
	Spawn(position, velocity);
}

void Shot::Destroy()
{
	Entity::Destroy();
}
