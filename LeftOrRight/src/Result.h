#pragma once
#include "Scene.h"
#include <array>

class Result :
	public Scene
{
	const Texture texture = Texture("res/results.png");
	Color color = Color(1, 1, 1);
	float radian = 0.0f;
public:
	Result(AppEnv&);

	SceneType Update();
	void Draw();

private:

};

