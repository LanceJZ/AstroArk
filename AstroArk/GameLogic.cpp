#include "GameLogic.h"

GameLogic::GameLogic()
{

	EM.AddEntity(PlayerClear = DBG_NEW Entity());
}

GameLogic::~GameLogic()
{
}

void GameLogic::SetPlayer(ThePlayer* player)
{
	Player = player;
}

void GameLogic::SetEnemies(EnemyControl* enemies)
{
	Enemies = enemies;
}

void GameLogic::SetBrickManager(TheBrickManager* brickManager)
{
	BrickManager = brickManager;
}

bool GameLogic::Initialize()
{
	Common::Initialize();

	AdjustedFieldSize = Vector2Multiply(FieldSize, { 0.5f, 0.5f });

	State = MainMenu;
	GameEnded = true;

	Score.SetPosition(335, 0);
	HighScore.SetPosition(1000, 0);

	return true;
}

bool GameLogic::BeginRun()
{
	Common::BeginRun();


	return false;
}

bool GameLogic::Load()
{
	return false;
}

void GameLogic::FixedUpdate()
{
	Common::FixedUpdate();

	CheckUFOBrickCollusions();
	CheckRockCollusions();

	if (State == Pause) IsPaused();
	if (State == MainMenu) InMainMenu();
	if (State == Player->GameOver) IsOver();
	if (State == InPlay) GamePlay();
}

void GameLogic::Input()
{
}

void GameLogic::NewGame()
{
	Player->NewGame();
	Enemies->NewGame();
	BrickManager->NewGame();
	GameEnded = false;
	State = InPlay;
	PlayerShipDisplay();
}

bool GameLogic::CheckPlayerClear()
{
	for (const auto& rock : Enemies->Rocks)
	{
		if (rock->Enabled && rock->CirclesIntersect(*PlayerClear))
		{
			return false;
		}
	}

	for (const auto& ufo : Enemies->UFOs)
	{
		if (ufo->Enabled && ufo->CirclesIntersect(*PlayerClear))
		{
			return false;
		}

		for (const auto& Shot : ufo->Shots)
		{
			if (Shot->Enabled && Shot->CirclesIntersect(*PlayerClear))
			{
				return false;
			}
		}
	}

	return true;
}

void GameLogic::PlayerShipDisplay()
{
	Vector2 location = { (-GetScreenWidth() / 2.05f) + Player->Radius,
		(-GetScreenHeight() / 2) + Player->Radius * 2.0f + 30.0f };

	if (Player->Lives > (int)PlayerShipModels.size())
	{
		AddPlayerShipModels(Player->Lives - (int)PlayerShipModels.size());
	}

	if (Player->Lives > (int)PlayerShipModels.size())
	{
		return;
	}

	for (const auto& model : PlayerShipModels)
	{
		model->Enabled = false;
		model->Position = { location.x, location.y, 0.0f };
		location.x += Player->Radius * 2.0f;
	}

	for (int i = 0; i < Player->Lives; i++)
	{
		PlayerShipModels.at(i)->Enabled = true;
	}
}

void GameLogic::AddPlayerShipModels(int number)
{
	for (int i = 0; i < number; i++)
	{
		PlayerShipModels.push_back(DBG_NEW LineModel());
		EM.AddLineModel(PlayerShipModels.back());
		PlayerShipModels.back()->SetModel(Player->GetLineModel());
		PlayerShipModels.back()->RotationZ = PI / 2 + PI;
		PlayerShipModels.back()->Scale = 0.8f;
		PlayerShipModels.back()->Radius = 0.0f;
	}
}

void GameLogic::GamePlay()
{
	if (Player->GetBeenHit())
	{
		//EM.ResetTimer(ExplodeTimerID);

		Player->Hit();
		Player->BeenHit = false;
		PlayerShipDisplay();

		if (State == Player->GameOver)
		{
			IsOver();
			return;
		}
	}

	//if (!EM.TimerElapsed(ExplodeTimerID)) return;

	if (!Player->Enabled && !Player->GetBeenHit())
	{
		PlayerClear->Enabled = true;
		PlayerClear->Radius = 140.0f;


		if (IsKeyPressed(KEY_ENTER) ||
			(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)))
		{
			PlayerClear->Radius = Player->Radius * 1.5f;
		}

		if (CheckPlayerClear())
		{
			Player->Spawn();
			PlayerClear->Enabled = false;
		}
	}
}

void GameLogic::CheckUFOBrickCollusions()
{
	for (const auto& brick : BrickManager->Bricks)
	{
		if (brick->Enabled)
		{
			for (const auto& ufo : Enemies->UFOs)
			{
				if (!ufo->Enabled) continue;

				if (brick->CirclesIntersect(*ufo))
				{
					ufo->Hit(brick->Position, { 0.0f });
					break;
				}

				for (const auto& shot : ufo->Shots)
				{
					if (!shot->Enabled) continue;

					if (brick->CirclesIntersect(*shot) ||
						brick->LeftSide->CirclesIntersect(*shot) ||
						brick->RightSide->CirclesIntersect(*shot))
					{
						shot->Hit(brick->Position, { 0.0f });
						brick->Hit(shot->Position, shot->Velocity);
						break;
					}
				}
			}
		}
	}
}

void GameLogic::CheckRockCollusions()
{
	for (const auto& rock : Enemies->Rocks)
	{
		if (rock->Enabled)
		{
			for (const auto& brick : BrickManager->Bricks)
			{
				if (brick->Enabled)
				{
					if (brick->CirclesIntersect(*rock) ||
						brick->LeftSide->CirclesIntersect(*rock) ||
						brick->RightSide->CirclesIntersect(*rock))
					{
						rock->Hit(brick->Position, { 0.0f });
					}
				}
			}
		}
	}
}

void GameLogic::IsOver()
{
	State = MainMenu;
	GameEnded = true;
}

void GameLogic::InMainMenu()
{
	if (!GameEnded)
	{
	}
	else
	{
		DrawText("N to Start Game", 500, 400, 40, WHITE);

		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 15))//Start button
			{
				NewGame();
			}
		}
		else if (IsKeyPressed(KEY_N))
		{
			NewGame();
		}
	}
}

void GameLogic::IsPaused()
{
		if (IsKeyPressed(KEY_P) || (IsGamepadAvailable(0)
			&& IsGamepadButtonPressed(0, 13)))
		{
			State = InPlay;
			Player->Paused = false;
		}

		return;
}
