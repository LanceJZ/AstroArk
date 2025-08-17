#include "TheBrick.h"

TheBrick::TheBrick()
{
	EM.AddEntity(LeftSide = DBG_NEW Entity());
	EM.AddEntity(RightSide = DBG_NEW Entity());
}

TheBrick::~TheBrick()
{
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
