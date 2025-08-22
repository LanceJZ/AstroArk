#pragma once
#include "Globals.h"
#include "Shot.h"

class ThePlayer : public LineModel
{
public:
	ThePlayer();
	virtual ~ThePlayer();

	bool NewLife = false;
	bool GameOver = false;
	bool Paused = false;
	int Lives = 0;

	LineModel* Shield = {};
	std::vector<Shot*> Shots = {};

	void SetFlameModel(LineModelPoints model);
	void SetShotModel(LineModelPoints model);
	void SetShieldModel(LineModelPoints model);
	void SetSounds(Sound explode, Sound fire, Sound thrust,
		Sound shieldOn, Sound shieldHit);

	bool Initialize();
	bool BeginRun();

	void Input();
	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void AlwaysUpdate(float deltaTime);
	void Draw3D();
	void Draw2D();

	void Hit();
	void ShieldHit(Vector3 position, Vector3 velocity);
	void Hit(Vector3 position, Vector3 velocity);
	void Reset();
	void Spawn();
	void NewGame();

private:
	size_t FireRateTimerID = 0;

	unsigned int NextNewLifeScore = 10000;
	unsigned int MagazineSize = 4;

	float ShieldPower = 0.0f;
	float ShieldDrainRate = 0.0f;
	float ShieldRechargeRate = 0.0f;

	float ShotLifeTime = 6.0f;

	Sound ExplodeSound = {};
	Sound FireSound = {};
	Sound ThrustSound = {};
	Sound ShieldOnSound = {};
	Sound ShieldHitSound = {};

	LineModelPoints ShotModel = { };
	LineModel* Flame = { nullptr };

	void FireShot();
	void ThrustOn(float amount);
	void ThrustOff();
	void ShieldOn();
	void ShieldOff();
	void ShieldPowerDrain(float deltaTime);

	void Gamepad();
	void Keyboard();
};
