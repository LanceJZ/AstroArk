#include "TheBrickManager.h"

TheBrickManager::TheBrickManager()
{

}

TheBrickManager::~TheBrickManager()
{
}

void TheBrickManager::SetBrickModel(Model model)
{
	BrickModel = model;
}

bool TheBrickManager::Initialize()
{
	Common::Initialize();


	return false;
}

bool TheBrickManager::BeginRun()
{
	BuildBricks();

	return false;
}

void TheBrickManager::Update()
{
	Common::Update();

}

void TheBrickManager::BuildBricks()
{
	float edge = 470.0f;
	float space = 32.0f;
	int bricks = 12;
	float lineSize = (bricks * space) / 2.0f;

	for (int i = 0; i < bricks; i++)
	{
		Bricks.push_back(DBG_NEW TheBrick());
		Bricks.back()->Initialize();
		EM.AddModel3D(Bricks.back());
		Bricks.back()->SetModel(BrickModel);
		Bricks.back()->BeginRun();
		Bricks.back()->X(-lineSize + 15 + (float)(i * space));
		Bricks.back()->Y(edge);
	}

	for (int i = 0; i < bricks; i++)
	{
		Bricks.push_back(DBG_NEW TheBrick());
		Bricks.back()->Initialize();
		EM.AddModel3D(Bricks.back());
		Bricks.back()->SetModel(BrickModel);
		Bricks.back()->BeginRun();
		Bricks.back()->X(-lineSize + 15 + (float)(i * space));
		Bricks.back()->Y(-edge);
	}

	for (int i = 0; i < bricks; i++)
	{
		Bricks.push_back(DBG_NEW TheBrick());
		Bricks.back()->Initialize();
		EM.AddModel3D(Bricks.back());
		Bricks.back()->SetModel(BrickModel);
		Bricks.back()->BeginRun();
		Bricks.back()->X(-edge);
		Bricks.back()->Y(-lineSize + 15 + (float)(i * space));
		Bricks.back()->RotationZ = HalfPi;
	}

	for (int i = 0; i < bricks; i++)
	{
		Bricks.push_back(DBG_NEW TheBrick());
		Bricks.back()->Initialize();
		EM.AddModel3D(Bricks.back());
		Bricks.back()->SetModel(BrickModel);
		Bricks.back()->BeginRun();
		Bricks.back()->X(edge);
		Bricks.back()->Y(-lineSize + 15 + (float)(i * space));
		Bricks.back()->RotationZ = HalfPi;
	}

	float anglespace = 22.5f;
	float startangle = 15.0f;

	for (int i = 0; i < bricks; i++)
	{
		Bricks.push_back(DBG_NEW TheBrick());
		Bricks.back()->Initialize();
		EM.AddModel3D(Bricks.back());
		Bricks.back()->SetModel(BrickModel);
		Bricks.back()->BeginRun();
		Bricks.back()->X((-lineSize - startangle - 1.5f) - (i * anglespace));
		Bricks.back()->Y((edge - startangle) - (i * anglespace));
		Bricks.back()->RotationZ = HalfPi / 2.0f;
	}

	for (int i = 0; i < bricks; i++)
	{
		Bricks.push_back(DBG_NEW TheBrick());
		Bricks.back()->Initialize();
		EM.AddModel3D(Bricks.back());
		Bricks.back()->SetModel(BrickModel);
		Bricks.back()->BeginRun();
		Bricks.back()->X((lineSize + startangle + 1.5f) + (i * anglespace));
		Bricks.back()->Y((edge - startangle) - (i * anglespace));
		Bricks.back()->RotationZ = -HalfPi / 2.0f;
	}

	for (int i = 0; i < bricks; i++)
	{
		Bricks.push_back(DBG_NEW TheBrick());
		Bricks.back()->Initialize();
		EM.AddModel3D(Bricks.back());
		Bricks.back()->SetModel(BrickModel);
		Bricks.back()->BeginRun();
		Bricks.back()->X((-lineSize - startangle - 1.5f) - (i * anglespace));
		Bricks.back()->Y((-edge + startangle) + (i * anglespace));
		Bricks.back()->RotationZ = -HalfPi / 2.0f;
	}

	for (int i = 0; i < bricks; i++)
	{
		Bricks.push_back(DBG_NEW TheBrick());
		Bricks.back()->Initialize();
		EM.AddModel3D(Bricks.back());
		Bricks.back()->SetModel(BrickModel);
		Bricks.back()->BeginRun();
		Bricks.back()->X((lineSize + startangle + 1.5f) + (i * anglespace));
		Bricks.back()->Y((-edge + startangle) + (i * anglespace));
		Bricks.back()->RotationZ = HalfPi / 2.0f;
	}
}
