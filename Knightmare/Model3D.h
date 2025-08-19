#pragma once
#include "Entity.h"

class Model3D : public Entity
{
public:
	Vector2 HalfViewableArea = { 0 };
	Vector3 ModelPosition = { 0 };
	Color ModelColor = WHITE;

	Model3D();
	~Model3D();

	bool SetCamera(Camera* camera);
	void SetModelWithTexture(Model &model, Texture2D &texture);
	virtual void Input();
	virtual bool Initialize();
	virtual bool BeginRun();
	virtual void Update(float deltaTime);
	virtual void FixedUpdate(float deltaTime);
	virtual void AlwaysUpdate(float deltaTime);
	virtual void Draw3D();

	void SetModel(Model &model, float scale);
	void SetModel(Model &model);
	void SetModelCopy(Model model, float scale);

	Camera* GetCamera();

	void Spawn(Vector3 pos);
	void Spawn(Vector3 pos, Vector3 vel);
	void Unload();

private:
};

