#include "TheUFO.h"

TheUFO::TheUFO()
{
}

TheUFO::~TheUFO()
{
}

bool TheUFO::Initialize()
{
	LineModel::Initialize();

	return false;
}

bool TheUFO::BeginRun()
{
	LineModel::BeginRun();

	return false;
}

void TheUFO::Update(float deltaTime)
{
	LineModel::Update(deltaTime);

}

void TheUFO::Draw3D()
{
	LineModel::Draw3D();
}

void TheUFO::Spawn(Vector3 position)
{
	Entity::Spawn(position);

}

void TheUFO::Destroy()
{
	Entity::Destroy();

}
