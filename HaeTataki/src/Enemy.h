#pragma once
#include "Object.h"
#include <vector>
#include <array>
#include "lib\random.hpp"
#include "lib\appEnv.hpp"
class Enemy :
	public Object
{
	enum class State{
		HIT,
		NORMAL
	};
	State state = State::NORMAL;
	Random random;
	std::vector<Texture>textures;
	Texture texture;
	AppEnv& app_env;
	std::array<Vec2f,9>effect_offset;
	int effect_count = 0;
	int& point;
	const Media hit_se = Media("res/hit.wav");
public:
	Enemy(AppEnv& app_env,ObjectInfo& object_info,int& point);

	void Update();
	void Draw();

private:
	void NormalDraw();
	void EffectDraw();
	void Reset();
};

