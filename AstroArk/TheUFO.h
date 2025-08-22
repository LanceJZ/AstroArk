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

	void Update(float deltaTime);
	void AlwaysUpdate(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Draw3D();

	void Spawn();
	void Destroy();

private:
	size_t VectorChangeTimerID = 0;
	size_t FireShotTimerID = 0;

	unsigned int WaveNumber = 0;

	void FireShot();
	void ChangeVector();

	bool CheckCollisions();

	float AimedShot();

};
