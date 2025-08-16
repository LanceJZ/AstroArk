#include "TheBrick.h"

TheBrick::TheBrick()
{
}

TheBrick::~TheBrick()
{
}

bool TheBrick::Initialize()
{
	Model3D::Initialize();

	return false;
}

bool TheBrick::BeginRun()
{
	Model3D::BeginRun();

	return false;
}

void TheBrick::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

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
