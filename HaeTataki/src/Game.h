#pragma once
#include "Scene.h"
#include "Object.h"
#include <unordered_map>
#include <vector>
class Game :
	public Scene
{
	ObjectInfo object_info;
	std::vector<std::shared_ptr<Object>>objects;
	const Texture bg_texture = Texture("res/game_bg.png");
	const Texture point_one_texture = Texture("res/miku_point_1.png");
	const Texture point_ten_texture = Texture("res/miku_point.png");
	int count_time;
	int point = 0;
public:
	Game(AppEnv&);

	SceneType Update();
	void Draw();
	static int MaxTime(){ 
		static const int max_time = 60 * 10;
		return max_time;
	}

private:
	void PointDraw();
	void ScoreSava();
};

