#pragma once
#include "Scene.h"
class Result :
	public Scene
{
	enum class State{
		START,
		SCORE,
	};

	State state = State::START;
	ObjectInfo object_info;
	std::vector<std::shared_ptr<Object>>objects;
	
	const Texture bg_texture = Texture("res/title_bg.png");
	const Texture end_string_texture = Texture("res/game_end.png");
	const Texture result_string = Texture("res/result.png");
	Media result_se = Media("res/end.wav");

public:
	Result(AppEnv&);
	~Result();

	SceneType Update();
	void Draw();
};

