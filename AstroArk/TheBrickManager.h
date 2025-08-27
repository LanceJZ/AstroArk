#pragma once
#include "Globals.h"
#include "TheBrick.h"
#include "ThePlayer.h"

class TheBrickManager : public Common
{
public:
	TheBrickManager();
	virtual ~TheBrickManager();

	std::vector<TheBrick*> Bricks;

	void SetBrickModel(Model model);
	void SetPlayerReference(ThePlayer* player);
	void SetSounds(Sound hitSound, Sound destroySound);

	bool Initialize();
	bool BeginRun();

	void Update();

	void NewGame();

private:
	Sound HitSound = { 0 };
	Sound DestroySound = { 0 };

	Model BrickModel = { 0 };

	Entity* MainLayer = nullptr;

	void BuildBricks();
	void PlaceBricks();

	ThePlayer* Player;
};

