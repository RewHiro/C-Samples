#include "Game.h"
#include "UITime.h"
#include "Player.h"
#include "Enemy.h"

Game::Game(AppEnv& app_env):
Scene(app_env),
count_time(MaxTime())
{
	LoadScene(SceneType::GAME);
	object_list.emplace("Player", std::make_shared<Player>(app_env));
	object_list.emplace("UITime", std::make_shared<UITime>(count_time));
	auto player = object_list.find("Player")->second;
	object_list.emplace("Enemy", std::make_shared<Enemy>(player));

	objects.emplace_back(object_list.find("UITime")->second);
	objects.emplace_back(object_list.find("Enemy")->second);
	objects.emplace_back(object_list.find("Player")->second);
}

SceneType Game::Update(){
	count_time--;

	for (auto& object : objects){
		object->Update();
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