#pragma once
#include "Scene.h"

class Title :
	public Scene
{

	const Texture bg_texture = Texture("res/title.png");
	Color color = Color(1, 1, 1);
	float radian = .0f;
public:
	Title(AppEnv&);

	SceneType Update();
	void Draw();

private:
};

