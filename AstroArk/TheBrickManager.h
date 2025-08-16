#pragma once
#include "Globals.h"
#include "TheBrick.h"

class TheBrickManager : public Common
{
public:
	TheBrickManager();
	virtual ~TheBrickManager();

	std::vector<TheBrick*> Bricks;

	void SetBrickModel(Model model);

	bool Initialize();
	bool BeginRun();

	void Update();

private:
	Model BrickModel = { 0 };

	void BuildBricks();
};

