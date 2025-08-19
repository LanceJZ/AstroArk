#pragma once
#include "Globals.h"
#include "ThePlayer.h"

class TheBrick : public Model3D
{
public:
	TheBrick();
	virtual ~TheBrick();

	void SetPlayerReference(ThePlayer* player);

	bool Initialize();
	bool BeginRun();

	void Update(float deltaTime);
	void FixedUpdate(float fixedDeltaTime);
	void Draw3D();

	void Spawn(Vector3 position);
	void Destroy();

private:
	size_t HitTimerID = 0;

	unsigned int Health = 4;
	unsigned int Points = 100;

	Entity* LeftSide = nullptr;
	Entity* RightSide = nullptr;

	ThePlayer* Player = nullptr;

	void Hit(Vector3 position, Vector3 velocity);
	void CheckCollision();

};
