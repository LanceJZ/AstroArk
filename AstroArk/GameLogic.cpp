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

	State = InPlay;

	Score.SetPosition(335, 0);
	HighScore.SetPosition(1000, 0);

	return true;
}

bool GameLogic::BeginRun()
{
	Common::BeginRun();

	GameEnded = true;

	return false;
}

bool GameLogic::Load()
{
	return false;
}

void GameLogic::FixedUpdate()
{
	Common::FixedUpdate();

	if (State == Pause)
	{
		if (IsKeyPressed(KEY_P) || (IsGamepadAvailable(0)
			&& IsGamepadButtonPressed(0, 13)))
		{
			State = InPlay;
			Player->Paused = false;
		}

		return;
	}
	if (State == MainMenu)
	{
		if (!GameEnded)
		{
		}
		else
		{
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
	else if (State == Player->GameOver)
	{
		IsOver();
	}
	else if (State == InPlay)
	{
		GamePlay();
	}
}

void GameLogic::Input()
{
}

void GameLogic::NewGame()
{
	Player->NewGame();
	Enemies->NewGame();
}

bool GameLogic::CheckPlayerClear()
{
	return true;
}

void GameLogic::GamePlay()
{
	for (const auto& brick : BrickManager->Bricks)
	{
		if (brick->Enabled)
		{
			for (const auto& ufo : Enemies->UFOs)
			{
				if (brick->CirclesIntersect(*ufo) && ufo->Enabled)
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
						break;
					}
				}
			}


		}
	}


	if (Player->GetBeenHit())
	{
		//EM.ResetTimer(ExplodeTimerID);

		Player->Destroy();

	}

	//if (!EM.TimerElapsed(ExplodeTimerID)) return;

	if (!Player->Enabled && !Player->GetBeenHit())
	{
		//PlayerClear->Enabled = true;
		//PlayerClear->Radius = 140.0f;

			Player->Spawn();
			PlayerClear->Enabled = false;

		if (IsKeyPressed(KEY_ENTER) ||
			(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)))
		{
			//PlayerClear->Radius = Player->Radius * 1.5f;
		}

		if (CheckPlayerClear())
		{
			//Player->Spawn();
			//PlayerClear->Enabled = false;
			//PlayerShipDisplay();
		}
	}
}

void GameLogic::IsOver()
{

}
