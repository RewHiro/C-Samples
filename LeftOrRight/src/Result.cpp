#include "Result.h"
#include "Game.h"

Result::Result(AppEnv& app_env):
Scene(app_env)
{
	LoadScene(SceneType::RESULT);
}

SceneType Result::Update(){
	radian += M_1_PI *.5f;
	color.red() = (std::sinf(radian) + 1.0f) / 2.0f;
	
	return Type();
}

void Result::Draw(){

	auto one_point = Game::Point() % 10;
	auto ten_point = Game::Point() / 10;
	auto x = -Window::WIDTH*.5f + 30;

	for (int i = 0; i < ten_point; i++){
		drawFillCircle(x, Window::HEIGHT * .5f - 30, 20, 20, 20, Color(1, 0, 0));
		x += 35;
	}
	for (int i = 0; i < one_point; i++){
		drawFillCircle(x, Window::HEIGHT * .5f - 30, 10, 10, 20, Color(1, 1, 0));
		x += 25;
	}

	drawTextureBox(0, 0, texture.width(), texture.height(),
		0, 0, texture.width(), texture.height(),
		texture, color,
		.0f,Vec2f::Ones(),Vec2f(texture.width()*.5f,texture.height()*.5f));
}

