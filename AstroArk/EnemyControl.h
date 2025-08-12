#pragma once
#include "Globals.h"
#include "ThePlayer.h"

class EnemyControl : public Common
{
public:
	EnemyControl();
	virtual ~EnemyControl();

	void SetPlayer(ThePlayer* player);

	bool Initialize();
	bool BeginRun();

	void Update();

	void NewGame();

private:

	ThePlayer *Player = nullptr;

	void Reset();
};