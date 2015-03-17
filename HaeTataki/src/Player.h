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
	Player(AppEnv& app_env,ObjectInfo& object_info);
	void Update();
	void Draw();
};

