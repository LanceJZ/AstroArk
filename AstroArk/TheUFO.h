#pragma once
#include "Globals.h"
#include "Enemy.h"

class TheUFO : public Enemy
{
public:
	TheUFO();
	virtual ~TheUFO();

	bool Initialize();
	bool BeginRun();

	void SetSounds(Sound explode, Sound fire, Sound active);

	void Update(float deltaTime);
	void AlwaysUpdate(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Draw3D();

	void Spawn();
	void Destroy();
	void Reset();

private:
	size_t VectorChangeTimerID = 0;
	size_t FireShotTimerID = 0;

	unsigned int WaveNumber = 0;

	Sound ExplodeSound = { 0 };
	Sound FireSound = { 0 };
	Sound ActiveSound = { 0 };

	void FireShot();
	void ChangeVector();

	bool CheckCollisions();

	float AimedShot();

};
