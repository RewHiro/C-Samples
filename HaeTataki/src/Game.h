#pragma once
#include "Scene.h"
#include "Object.h"
#include <unordered_map>
#include <vector>
class Game :
	public Scene
{
	std::vector<std::shared_ptr<Object>>objects;
	std::unordered_multimap<std::string, std::shared_ptr<Object>>object_list;
	const Texture bg_texture = Texture("res/game_bg.png");
	int count_time;
public:
	Game(AppEnv&);

	SceneType Update();
	void Draw();
	static int MaxTime(){ 
		static const int max_time = 60 * 10;
		return max_time;
	}
};

