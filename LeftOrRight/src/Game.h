#pragma once
#include "Scene.h"
#include <random>
#include <array>

class Game :
	public Scene
{
	struct CardInfo{
		Vec2f texture_pos;
		Vec2f texture_size;
		int num;
	};
	std::mt19937 random;
	std::array<CardInfo, 52>card_info;
	const Texture card_texture = Texture("res/cards.png");
	const Vec2f CUTTING_SIZE = Vec2f(72, 96);
	Vec2f left_pos = Vec2f(-100, 0);
	Vec2f right_pos = Vec2f(100, 0);
	Vec2f card_size = Vec2f(72, 96);
	Color left_color = Color(1, 1, 1);
	Color right_color = Color(1, 1, 1);
	const int MAX_TIME = 60 * 15;
	const int CUTTING_NUM = 13;
	int time = MAX_TIME;
	int card_index = 0;
	int point = 0;


public:
	Game(AppEnv&);

	SceneType Update();
	void Draw();

	static int& Point(){
		static int point = 0;
		return point; 
	}

private:
};

