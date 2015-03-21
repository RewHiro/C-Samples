#include "Result.h"
#include "ClickToTitle.h"
#include <fstream>

Result::Result(AppEnv& app_env):
Scene(app_env)
{
	LoadScene(SceneType::RESULT);

	result_se.play();

	objects.emplace_back(std::make_shared<ClickToTitle>(object_info));
	object_info.Add("ClickToTitle", objects.at(0));

	std::ifstream score_text("res/score.txt");
	score_text >> score;

	int hi_score = 0;
	std::ifstream hi_score_text("res/hi_score.txt");
	hi_score_text >> hi_score;

	if(score > hi_score){
		std::ofstream save("res/hi_score.txt");
		save << score;
		is_hi_score = !is_hi_score;
	}

	std::array<Color,4>array = {
		Color(0, 0, 1),
		Color(0, 1, 1),
		Color(1, 0, 0),
		Color(1, 0, 1),
	};

	color_array = array;
}

SceneType Result::Update(){
	if(state == State::START){
		if(!result_se.isPlaying()){
			state = State::SCORE;
		}
	}
	else{
		for(auto& object : objects){
			object->Update();
		}
		if(app_env.isPushButton(Mouse::LEFT)){
			LoadScene(SceneType::TITLE);
		}
		if(is_hi_score){
			effect_count++;
			hi_score_color = color_array.at(effect_count / 10 % 4);
		}
	}
	return Type();
}

void Result::Draw(){
	//@”wŒi
	drawTextureBox(-Window::WIDTH *.5f, -Window::HEIGHT*.5f, bg_texture.width(), bg_texture.height(),
		0, 0, bg_texture.width(), bg_texture.height(),
		bg_texture, Color(1, 1, 1));

	PointDraw();

	if(state == State::START){
	//@I—¹
	drawTextureBox(0, 0, end_string_texture.width(), end_string_texture.height(),
		0, 0, end_string_texture.width(), end_string_texture.height(),
		end_string_texture, Color(1, 1, 1),
		.0f, Vec2f(1, 1), Vec2f(end_string_texture.width()*.5f, end_string_texture.height()*.5f));
	}
	else {
		drawTextureBox(0, 100, result_string.width(), result_string.height(),
			0, 0, result_string.width(), result_string.height(),
			result_string, Color(1, 1, 1),
			.0f, Vec2f(1, 1), Vec2f(result_string.width()*.5f, result_string.height()*.5f));
		if(is_hi_score){
			drawTextureBox(0, 0, hi_score_string.width(),hi_score_string.height(),
				0, 0, hi_score_string.width(), hi_score_string.height(),
				hi_score_string, hi_score_color,
				.0f, Vec2f(1, 1), Vec2f(hi_score_string.width()*.5f, hi_score_string.height()*.5f));
		}


		for (auto& object : objects){
			object->Draw();
		}
	}	
}

void Result::PointDraw(){
	auto x = 0;
	auto point_one = score % 10;
	auto point_ten = score / 10;

	for (int i = 0; i < point_ten; i++){
		drawTextureBox(x - Window::WIDTH*.5f, -Window::HEIGHT*.5f, 80, 80,
			0, 0, 80, 80,
			point_ten_texture, Color(1, 1, 1));
		x += 15;
	}
	for (int i = 0; i < point_one; i++){
		drawTextureBox(x - Window::WIDTH*.5f, -Window::HEIGHT*.5f, 60, 60,
			0, 0, 80, 80,
			point_one_texture, Color(1, 1, 1));
		x += 15;
	}
}