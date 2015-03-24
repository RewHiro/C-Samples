#include "Title.h"
#include "lib\appEnv.hpp"


Title::Title(AppEnv& app_env):
Scene(app_env)
{
	LoadScene(SceneType::TITLE);
}

SceneType Title::Update(){
	radian += static_cast<float>(M_1_PI * .1f);
	color.alpha() = std::fabsf(std::sinf(radian));

	if(app_env.isPushButton(Mouse::LEFT) || app_env.isPullButton(Mouse::RIGHT)){
		LoadScene(SceneType::GAME);
	}
	return Type();
}

void Title::Draw(){
	drawTextureBox(0, 50, 270, 280,
		0, 0, 270, 280,
		bg_texture, Color(1, 0, 0),
		.0f,Vec2f::Ones(),Vec2f(270*.5f,280*.5f));

	drawTextureBox(0, -140, 430, 55,
		40, 295, 430, 55,
		bg_texture, color,
		.0f, Vec2f::Ones(), Vec2f(430 * .5f, 55 * .5f));
}

