#include "TheBrickManager.h"

TheBrickManager::TheBrickManager()
{
	EM.AddEntity(MainLayer = DBG_NEW Entity());
}

TheBrickManager::~TheBrickManager()
{
}

void TheBrickManager::SetBrickModel(Model model)
{
	BrickModel = model;
}

void TheBrickManager::SetPlayerReference(ThePlayer* player)
{
	Player = player;
}

void TheBrickManager::SetSounds(Sound hitSound, Sound destroySound)
{
	HitSound = hitSound;
	DestroySound = destroySound;
}

bool TheBrickManager::Initialize()
{
	Common::Initialize();


	return false;
}

bool TheBrickManager::BeginRun()
{
	BuildBricks();
	PlaceBricks();

	MainLayer->RotationVelocityZ = 0.01f;

	return false;
}

void TheBrickManager::Update()
{
	Common::Update();

	bool reset = true;

	for (const auto& brick : Bricks)
	{
		if (brick->Enabled) reset = false;
	}

	if (reset) NewGame();
}

void TheBrickManager::NewGame()
{
	for (const auto& brick : Bricks)
	{
		brick->Spawn();
	}

	MainLayer->RotationZ = 0.0f;
}

void TheBrickManager::BuildBricks()
{
	int bricks = 12;
	int lines = 8;

	for (int i = 0; i < lines * bricks; i++)
	{
		Bricks.push_back(DBG_NEW TheBrick());
		Bricks.back()->Initialize();
		EM.AddModel3D(Bricks.back());
		Bricks.back()->SetModel(BrickModel);
		Bricks.back()->SetPlayerReference(Player);
		Bricks.back()->SetSounds(HitSound, DestroySound);
		Bricks.back()->SetParent(*MainLayer);
		Bricks.back()->BeginRun();
	}
}

void TheBrickManager::PlaceBricks()
{
	float edge = 470.0f;
	float space = 32.0f;
	int bricks = 12;
	float lineSize = (bricks * space) / 2.0f;

	for (int i = 0; i < bricks; i++)
	{
		Bricks.at(i)->X(-lineSize + 15 + (float)(i * space));
		Bricks.at(i)->Y(edge);
	}

	for (int i = 0; i < bricks; i++)
	{
		Bricks.at(i + (bricks * 1))->X(-lineSize + 15 + (float)(i * space));
		Bricks.at(i + (bricks * 1))->Y(-edge);
	}

	for (int i = 0; i < bricks; i++)
	{
		Bricks.at(i + (bricks * 2))->X(-edge);
		Bricks.at(i + (bricks * 2))->Y(-lineSize + 15 + (float)(i * space));
		Bricks.at(i + (bricks * 2))->RotationZ = HalfPi;
	}

	for (int i = 0; i < bricks; i++)
	{
		Bricks.at(i + (bricks * 3))->X(edge);
		Bricks.at(i + (bricks * 3))->Y(-lineSize + 15 + (float)(i * space));
		Bricks.at(i + (bricks * 3))->RotationZ = HalfPi;
	}

	float aspace = 22.5f;
	float sangle = 15.0f;

	for (int i = 0; i < bricks; i++)
	{
		Bricks.at(i + (bricks * 4))->X((-lineSize - sangle - 1.5f) - (i * aspace));
		Bricks.at(i + (bricks * 4))->Y((edge - sangle) - (i * aspace));
		Bricks.at(i + (bricks * 4))->RotationZ = HalfPi / 2.0f;
	}

	for (int i = 0; i < bricks; i++)
	{
		Bricks.at(i + (bricks * 5))->X((lineSize + sangle + 1.5f) + (i * aspace));
		Bricks.at(i + (bricks * 5))->Y((edge - sangle) - (i * aspace));
		Bricks.at(i + (bricks * 5))->RotationZ = -HalfPi / 2.0f;
	}

	for (int i = 0; i < bricks; i++)
	{
		Bricks.at(i + (bricks * 6))->X((-lineSize - sangle - 1.5f) - (i * aspace));
		Bricks.at(i + (bricks * 6))->Y((-edge + sangle) + (i * aspace));
		Bricks.at(i + (bricks * 6))->RotationZ = -HalfPi / 2.0f;
	}

	for (int i = 0; i < bricks; i++)
	{
		Bricks.at(i + (bricks * 7))->X((lineSize + sangle + 1.5f) + (i * aspace));
		Bricks.at(i + (bricks * 7))->Y((-edge + sangle) + (i * aspace));
		Bricks.at(i + (bricks * 7))->RotationZ = HalfPi / 2.0f;
	}
}
