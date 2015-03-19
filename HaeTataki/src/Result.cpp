#include "Result.h"
#include "ClickToTitle.h"

Result::Result(AppEnv& app_env):
Scene(app_env)
{
	LoadScene(SceneType::RESULT);

	result_se.play();

	objects.emplace_back(std::make_shared<ClickToTitle>(object_info));
	object_info.Add("ClickToTitle", objects.at(0));
}


Result::~Result()
{
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
	}
	return Type();
}

void Result::Draw(){
	//@”wŒi
	drawTextureBox(-Window::WIDTH *.5f, -Window::HEIGHT*.5f, bg_texture.width(), bg_texture.height(),
		0, 0, bg_texture.width(), bg_texture.height(),
		bg_texture, Color(1, 1, 1));
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

		for (auto& object : objects){
			object->Draw();
		}
	}
	
}