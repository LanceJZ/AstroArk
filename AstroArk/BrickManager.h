#pragma once
#include "Globals.h"

class BrickManager : public Common
{
public:
	BrickManager();
	virtual ~BrickManager();

	bool Initialize();
	bool BeginRun();

	void Update();

private:


};

