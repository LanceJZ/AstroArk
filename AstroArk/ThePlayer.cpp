#include "ThePlayer.h"

ThePlayer::ThePlayer()
{

	EM.AddLineModel(Flame = DBG_NEW LineModel());
	EM.AddLineModel(Shield = DBG_NEW LineModel());

	for (int i = 0; i < MagazineSize; i++)
	{
		Shots.push_back(DBG_NEW Shot());
		EM.AddLineModel(Shots.back());
	}

	FireRateTimerID = EM.AddTimer(0.5f);
}

ThePlayer::~ThePlayer()
{
}

void ThePlayer::SetFlameModel(LineModelPoints model)
{
	Flame->SetModel(model);
}

void ThePlayer::SetShotModel(LineModelPoints model)
{
	for (auto& shot : Shots)
	{
		shot->SetModel(model);
	}

	ShotModel = model;
}

void ThePlayer::SetShieldModel(LineModelPoints model)
{
	Shield->SetModel(model);
}

void ThePlayer::SetSounds(Sound explode, Sound fire, Sound thrust,
		Sound shieldOn, Sound shieldHit)
{
	ExplodeSound = explode;
	FireSound = fire;
	ThrustSound = thrust;
	ShieldOnSound = shieldOn;
	ShieldHitSound = shieldHit;
}

bool ThePlayer::Initialize()
{
	LineModel::Initialize();

	Flame->Enabled = false;
	Shield->Enabled = false;
	Enabled = false;
	GameOver = true;

	return false;
}

bool ThePlayer::BeginRun()
{
	LineModel::BeginRun();

	Flame->SetParent(*this);
	Shield->SetParent(*this);

	return false;
}

void ThePlayer::Input()
{
	LineModel::Input();

	Keyboard();

	if (IsGamepadAvailable(0))
	{
		Gamepad();
	}
}

void ThePlayer::Update(float deltaTime)
{
	LineModel::Update(deltaTime);

}

void ThePlayer::FixedUpdate(float deltaTime)
{
	LineModel::FixedUpdate(deltaTime);

	ShieldPowerDrain(deltaTime);
	CheckScreenEdge();
}

void ThePlayer::AlwaysUpdate(float deltaTime)
{
	LineModel::AlwaysUpdate(deltaTime);
}

void ThePlayer::Draw3D()
{
	LineModel::Draw3D();

}

void ThePlayer::Draw2D()
{
	LineModel::Draw2D();

}

void ThePlayer::Hit()
{
	Entity::Hit();

	PlaySound(ExplodeSound);

	Enabled = false;
	Flame->Enabled = false;
	Acceleration = { 0 };
	Velocity = { 0 };
	Lives--;

	if (Lives <= 0)
	{
		GameOver = true;
	}
}

void ThePlayer::ShieldHit(Vector3 position, Vector3 velocity)
{
	Hit(position, velocity);
	PlaySound(ShieldHitSound);
}

void ThePlayer::Hit(Vector3 position, Vector3 velocity)
{
	Velocity = GetReflectionVelocity(position, velocity, 200.0f);
}

void ThePlayer::Reset()
{
	Position = { 0, 0, 0 };
	Velocity = { 0, 0, 0 };
	Enabled = true;
	ShieldPower = 100.0f;
	Shield->ModelColor = WHITE;
}

void ThePlayer::Spawn()
{
	Reset();
}

void ThePlayer::NewGame()
{
	Lives = 4;
	NextNewLifeScore = 10000;
	GameOver = false;
	Reset();
}

void ThePlayer::FireShot()
{
	for (auto& shot : Shots)
	{
		if (!shot->Enabled && EM.TimerElapsed(FireRateTimerID))
		{
			PlaySound(FireSound);
			EM.ResetTimer(FireRateTimerID);
			Vector3 velocity = GetVelocityFromAngleZ(RotationZ, 400.0f);
			velocity = Vector3Add(Vector3Multiply(Velocity,
				{ 0.5f, 0.5f, 0.0f }), velocity);
			shot->Spawn(Position, velocity, ShotLifeTime);
			break;
		}
	}
}

void ThePlayer::ThrustOn(float amount)
{
	if (!IsSoundPlaying(ThrustSound)) PlaySound(ThrustSound);

	Flame->Enabled = true;
	Acceleration = GetAccelerationToMaxAtRotation((amount * 50.25f), 350.0f);

}

void ThePlayer::ThrustOff()
{
	Flame->Enabled = false;
	SetAccelerationToZero(0.45f);

	StopSound(ThrustSound);
}

void ThePlayer::ShieldOn()
{
	if (ShieldPower > 0.0f)
	{
		Shield->Enabled = true;

		if (!IsSoundPlaying(ShieldOnSound)) PlaySound(ShieldOnSound);
		{
			Shield->Alpha = ShieldPower * 2.55f;
		}
	}
	else
	{
		ShieldOff();
	}
}

void ThePlayer::ShieldOff()
{
	StopSound(ShieldOnSound);
	Shield->Enabled = false;
}

void ThePlayer::ShieldPowerDrain(float deltaTime)
{
	if (Shield->Enabled)
	{
		ShieldPower -= ShieldDrainRate * deltaTime;

		if (ShieldPower < 0.0f)	ShieldPower = 0.0f;
	}
	else
	{
		if (ShieldPower < 100.0f) ShieldPower += ShieldRechargeRate * deltaTime;
	}
}

void ThePlayer::Gamepad()
{
	//Button B is 6 for Shield //Button A is 7 for Fire //Button Y is 8 for Hyperspace
	//Button X is 5	//Left bumper is 9 //Right bumper is 11 for Shield //Left Trigger is 10
	//Right Trigger is 12 for Thrust //Dpad Up is 1 for	//Dpad Down is 3 for
	//Dpad Left is 4 for rotate left //Dpad Right is 2 for rotate right
	//Axis 1 is -1 for , 1 for  on left stick.
	//Axis 0 is -1 for Left, 1 for right on left stick.

	if (IsGamepadButtonDown(0, 12))
	{
	}
	else
	{
	}

	if (IsGamepadButtonDown(0, 4) || GetGamepadAxisMovement(0, 0) < -0.25f)
	{
	}
	else if (IsGamepadButtonDown(0, 2) || GetGamepadAxisMovement(0, 0) > 0.25f)
	{
	}

	if (IsGamepadButtonPressed(0, 7))
	{
	}

	if (IsGamepadButtonDown(0, 11) || IsGamepadButtonDown(0, 6))
	{
	}
	else
	{
	}
}

void ThePlayer::Keyboard()
{
	float velocityRotZ = 3.666f;

	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
	{
		RotationVelocityZ = velocityRotZ;
	}
	else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
	{
		RotationVelocityZ = -velocityRotZ;
	}
	else
	{
		RotationVelocityZ = 0;
	}

	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
	{
		ThrustOn(1.0f);
	}
	else
	{
		ThrustOff();
	}

	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
	{
		ShieldOn();
	}
	else
	{
		ShieldOff();
	}

	if (IsKeyPressed(KEY_RIGHT_CONTROL) || IsKeyPressed(KEY_LEFT_CONTROL) ||
		IsKeyPressed(KEY_SPACE))
	{
		FireShot();
	}

	if (IsKeyDown(KEY_DOWN))
	{
	}
	else
	{
	}
}