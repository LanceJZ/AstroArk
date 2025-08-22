#pragma once
#include "Globals.h"
#include "ThePlayer.h"

class TheBrick : public Model3D
{
public:
	TheBrick();
	virtual ~TheBrick();

	Entity* LeftSide = nullptr;
	Entity* RightSide = nullptr;

	void SetPlayerReference(ThePlayer* player);
	void SetSounds(Sound hitSound, Sound destroySound);

	bool Initialize();
	bool BeginRun();

	void Update(float deltaTime);
	void FixedUpdate(float fixedDeltaTime);
	void AlwaysUpdate(float deltaTime);
	void Draw3D();

	void Spawn(Vector3 position);
	void Destroy();

	void Hit(Vector3 position, Vector3 velocity);

private:
	size_t HitTimerID = 0;

	unsigned int Health = 4;
	unsigned int Points = 100;

	Sound HitSound = { 0 };
	Sound DestroySound = { 0 };

	ThePlayer* Player = nullptr;

	void PlayerHit();
	void CheckCollision();

};
