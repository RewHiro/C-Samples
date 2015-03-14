#pragma once
#include "Scene.h"
#include "Object.h"
#include <map>
#include <memory>

class Title :
	public Scene
{
	std::multimap<std::string, std::shared_ptr<Object>>object_list;
	const Texture bg = Texture("res/title_bg.png");
	const Texture title_texture = Texture("res/logo.png");
	const Media title_se = Media("res/title.wav");
	const Media start_se = Media("res/start.wav");
	bool is_transition = false;
	const int TRANSITION_TIME = 60 * 2;
	int transiton_count = 0;
public:
	Title(AppEnv&);

	SceneType Update();
	void Draw();

private:
	void StartTrasition();
	void TransitionCondition();
};

