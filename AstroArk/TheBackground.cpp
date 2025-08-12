#include "TheBackground.h"

TheBackground::TheBackground()
{
	EM.AddModel3D(Ground = DBG_NEW Model3D());
}

TheBackground::~TheBackground()
{
}

bool TheBackground::Initialize()
{
	Common::Initialize();

	return false;
}

bool TheBackground::BeginRun()
{

	return false;
}

void TheBackground::SetGroundModel(Model& model)
{
	Ground->SetModel(model);
}

void TheBackground::Update()
{
	Common::Update();

}