#pragma once
#include "Object.h"
#include "lib\random.hpp"
#include <vector>
class Enemy :
	public Object
{
	std::weak_ptr<Object> col_pos;
	Random random;
	std::vector<Texture>textures;
	Texture texture;
public:
	Enemy(std::weak_ptr<Object> col_pos);

	void Update();
	void Draw();
};

