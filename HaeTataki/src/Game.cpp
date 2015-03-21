#include "Game.h"
#include "UITime.h"
#include "Player.h"
#include "Enemy.h"
#include <fstream>

Game::Game(AppEnv& app_env):
Scene(app_env),
count_time(MaxTime())
{
	LoadScene(SceneType::GAME);
	objects.emplace_back(std::make_shared<Enemy>(app_env, object_info,point));
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
		ScoreSava();
		LoadScene(SceneType::RESULT);
	}

	return Type();
}

void Game::Draw(){

	//@”wŒi
	drawTextureBox(-Window::WIDTH *.5f, -Window::HEIGHT*.5f, bg_texture.width(), bg_texture.height(),
		0, 0, bg_texture.width(), bg_texture.height(),
		bg_texture, Color(1, 1, 1));
	PointDraw();
	for (auto& object : objects){
		object->Draw();
	}
}

void Game::PointDraw(){
	auto x = 0;
	auto point_one = point % 10;
	auto point_ten = point / 10;

	for (int i = 0; i < point_ten; i++){
		drawTextureBox(x - Window::WIDTH*.5f, -Window::HEIGHT*.5f, 80, 80,
			0, 0, 80, 80,
			point_ten_texture, Color(1, 1, 1));
		x += 15;
	}
	for (int i = 0; i < point_one; i++){
		drawTextureBox(x -Window::WIDTH*.5f, -Window::HEIGHT*.5f, 60, 60,
			0, 0, 80, 80,
			point_one_texture, Color(1, 1, 1));
		x += 15;
	}
}

void Game::ScoreSava(){
	std::ofstream save("res/score.txt");
	save << point;
}