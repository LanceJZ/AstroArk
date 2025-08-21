#pragma once
#include "Globals.h"
#include "LineModel.h"

class TheUFO : public LineModel
{
public:
	TheUFO();
	virtual ~TheUFO();

	bool Initialize();
	bool BeginRun();

	void Update(float deltaTime);
	void Draw3D();

	void Spawn(Vector3 position);
	void Destroy();

private:


};
