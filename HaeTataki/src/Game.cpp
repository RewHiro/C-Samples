#include "Game.h"
#include "UITime.h"
#include "Player.h"
#include "Enemy.h"

Game::Game(AppEnv& app_env):
Scene(app_env),
count_time(MaxTime())
{
	LoadScene(SceneType::GAME);
	objects.emplace_back(std::make_shared<Enemy>(app_env, object_info));
	objects.emplace_back(std::make_shared<UITime>(count_time, object_info));
	objects.emplace_back(std::make_shared<Player>(app_env, object_info));

	object_info.Add("Enemy", objects.at(0));
	object_info.Add("UITime", objects.at(1));
	object_info.Add("Player", objects.at(2));
}

SceneType Game::Update(){
	count_time--;

	for (auto& object : objects){
		object->Update();
	}
	if(count_time <= 0){
		LoadScene(SceneType::RESULT);
	}

	return Type();
}

void Game::Draw(){

	//@”wŒi
	drawTextureBox(-Window::WIDTH *.5f, -Window::HEIGHT*.5f, bg_texture.width(), bg_texture.height(),
		0, 0, bg_texture.width(), bg_texture.height(),
		bg_texture, Color(1, 1, 1));

	for (auto& object : objects){
		object->Draw();
	}

}