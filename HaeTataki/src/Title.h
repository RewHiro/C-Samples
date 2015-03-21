#pragma once
#include "Scene.h"
#include "Object.h"
#include <map>
#include <memory>

class Title :
	public Scene
{
	ObjectInfo object_info;
	std::vector<std::shared_ptr<Object>>objects;
	const Texture bg = Texture("res/title_bg.png");
	const Texture title_texture = Texture("res/logo.png");
	const Media title_se = Media("res/title.wav");
	const Media start_se = Media("res/start.wav");
	const Texture point_one_texture = Texture("res/miku_point_1.png");
	const Texture point_ten_texture = Texture("res/miku_point.png");
	bool is_transition = false;
	const int TRANSITION_TIME = 60 * 2;
	int transiton_count = 0;
	int score = 0;
public:
	Title(AppEnv&);

	SceneType Update();
	void Draw();

private:
	void StartTrasition();
	void TransitionCondition();
	void PointDraw();
};

