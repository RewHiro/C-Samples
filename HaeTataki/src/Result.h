#pragma once
#include "Scene.h"
#include <array>

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
	const Texture point_one_texture = Texture("res/miku_point_1.png");
	const Texture point_ten_texture = Texture("res/miku_point.png");
	const Texture hi_score_string = Texture("res/hi_score.png");
	Media result_se = Media("res/end.wav");
	Color hi_score_color = Color(1, 1, 1);
	std::array<Color, 4>color_array;
	int effect_count = 0;

	int score = 0;
	bool is_hi_score = false;
public:
	Result(AppEnv&);

	SceneType Update();
	void Draw();

private:
	void PointDraw();
};

