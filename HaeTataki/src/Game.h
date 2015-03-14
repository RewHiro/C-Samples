#pragma once
#include "Scene.h"
class Game :
	public Scene
{
public:
	Game(AppEnv&);

	SceneType Update();
	void Draw();
};

