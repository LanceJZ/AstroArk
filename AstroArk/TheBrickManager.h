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

	bool Initialize();
	bool BeginRun();

	void Update();

private:
	Model BrickModel = { 0 };

	void BuildBricks();
	void PlaceBricks();

	ThePlayer* Player;
};

