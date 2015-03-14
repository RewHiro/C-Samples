#include "Game.h"


Game::Game(AppEnv& app_env):
Scene(app_env)
{
	LoadScene(SceneType::GAME);
}

SceneType Game::Update(){

	if (app_env.isPushButton(Mouse::LEFT)){
		LoadScene(SceneType::TITLE);
	}

	return Type();
}

void Game::Draw(){
}