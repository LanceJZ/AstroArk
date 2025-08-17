#pragma once
#include "Globals.h"
#include "Model3D.h"

class TheBrick : public Model3D
{
public:
	TheBrick();
	virtual ~TheBrick();

	bool Initialize();
	bool BeginRun();

	void Update(float deltaTime);
	void Draw3D();

	void Spawn(Vector3 position);
	void Destroy();

private:
	Entity* LeftSide = nullptr;
	Entity* RightSide = nullptr;

};
