#pragma once
#include "Object.h"
#include "lib\appEnv.hpp"
#include <vector>

class Player :
	public Object
{
	AppEnv& app_env;
	Texture texture;
	std::vector<Texture> textures;
public:
	Player(AppEnv& app_env);
	void Update();
	void Draw();
};

