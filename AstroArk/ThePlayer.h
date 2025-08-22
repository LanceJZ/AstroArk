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

	std::vector<Shot*> Shots = {};

	void SetFlameModel(LineModelPoints model);
	void SetShotModel(LineModelPoints model);
	void SetSounds(Sound explode, Sound fire, Sound thrust);

	bool Initialize();
	bool BeginRun();

	void Input();
	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void AlwaysUpdate(float deltaTime);
	void Draw3D();
	void Draw2D();

	void Hit();
	void Hit(Vector3 position, Vector3 velocity);
	void Reset();
	void Spawn();
	void NewGame();

private:
	size_t FireRateTimerID = 0;

	int NextNewLifeScore = 10000;
	int MagazineSize = 4;

	float ShotLifeTime = 6.0f;

	Sound ExplodeSound;
	Sound FireSound;
	Sound ThrustSound;

	LineModelPoints ShotModel = { };
	LineModel* Flame = { nullptr };

	void FireShot();
	void ThrustOn(float amount);
	void ThrustOff();

	void Gamepad();
	void Keyboard();
};
