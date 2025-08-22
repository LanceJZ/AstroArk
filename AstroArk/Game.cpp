#include "Game.h"

Game::Game()
{
	//When adding classes to EM, must be pointer to heap,IE: Name = new Class().

	LogicID = EM.AddCommon(Logic = DBG_NEW GameLogic());
	BackGroundID = EM.AddCommon(BackGround = DBG_NEW TheBackground());
	BrickManagerID = EM.AddCommon(BrickManager = DBG_NEW TheBrickManager());
	EnemiesID = EM.AddCommon(Enemies = DBG_NEW EnemyControl());
	PlayerID = EM.AddLineModel(Player = DBG_NEW ThePlayer());
}

Game::~Game()
{
}

bool Game::Initialize() //Initialize
{
	Common::Initialize();

	float multiW = 1.0f, multiH = 1.0f;
	FieldSize = { GetScreenWidth() * multiW, (float)GetScreenHeight() * multiH };

	Logic->SetPlayer(Player);
	Logic->SetEnemies(Enemies);
	Logic->SetBrickManager(BrickManager);

	Enemies->SetPlayer(Player);

	BrickManager->SetPlayerReference(Player);

	//Any Entities added after this point need this method fired manually.

	return true;
}

//..
// Model Names:
// PlayerShip, PlayerFlame, Brick, UFO, Dot
//..
bool Game::Load()
{
	size_t shotModelID = CM.LoadTheLineModel("Dot");


	Player->SetModel(CM.LoadAndGetLineModel("PlayerShip"));
	Player->SetFlameModel(CM.LoadAndGetLineModel("PlayerFlame"));
	Player->SetShotModel(CM.GetLineModel(shotModelID));


	BrickManager->SetBrickModel(CM.LoadAndGetModel("Brick"));

	LineModelPoints rockModels[4];

	rockModels[0] = CM.LoadAndGetLineModel("Rock1");
	rockModels[1] = CM.LoadAndGetLineModel("Rock2");
	rockModels[2] = CM.LoadAndGetLineModel("Rock3");
	rockModels[3] = CM.LoadAndGetLineModel("Rock4");

	Enemies->SetRockModels(rockModels);
	Enemies->SetUFOModel(CM.LoadAndGetLineModel("UFO"));
	Enemies->SetShotModel(CM.GetLineModel(shotModelID));

	//Sounds

	Player->SetSounds(CM.LoadAndGetSound("PlayerExplode"),
		CM.LoadAndGetSound("PlayerFire"), CM.LoadAndGetSound("PlayerThrust"));

	Enemies->SetRockExplodeSound(CM.LoadAndGetSound("RockExplode"));
	Enemies->SetUFOSounds(CM.LoadAndGetSound("UFOExplode"),
		CM.LoadAndGetSound("UFOFire"), CM.LoadAndGetSound("UFOBig"));

	BrickManager->SetSounds(CM.LoadAndGetSound("BossHit"),
		CM.LoadAndGetSound("PowerUp"));

	return true;
}

bool Game::BeginRun()
{
	//Any Entities added after this point need this method fired manually.

	return true;
}

void Game::Input()
{
	GameInput();
}


void Game::Update(float deltaTime)
{
	if (Logic->State == Pause)	return;
}

void Game::FixedUpdate(float deltaTime)
{
	if (Logic->State == Pause)	return;
}

void Game::Draw()
{
	BeginMode3D(TheCamera);

	//3D Drawing here.
	Draw3D();

	EndMode3D();

	//2D drawing, fonts go here.

	Draw2D();
}

void Game::Draw3D()
{

#ifdef _DEBUG
	int fsx = int(FieldSize.x * 0.5f);
	int fsy = int(FieldSize.y * 0.5f);

	DrawLine(-fsx, -fsy, fsx, -fsy, { DARKBLUE });
	DrawLine(fsx, -fsy, fsx, fsy, { DARKBLUE });
	DrawLine(fsx, fsy - 1, -fsx, fsy, { DARKBLUE });
	DrawLine(-fsx, fsy - 1, -fsx, -fsy, { DARKBLUE });
#endif
}

void Game::Draw2D()
{
}

void Game::GameInput()
{
	Logic->Input();

	if (IsKeyPressed(KEY_P))
	{
		if (Logic->State == Pause) Logic->State = InPlay;
		else if (Logic->State == InPlay) Logic->State = Pause;
	}

	if (Logic->State == Ended)
	{
		if (IsKeyPressed(KEY_N)) Logic->NewGame();
	}
}