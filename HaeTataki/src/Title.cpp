#include "Title.h"
#include "lib\appEnv.hpp"
#include "ClickToStart.h"



Title::Title(AppEnv& app_env):
Scene(app_env)
{
	LoadScene(SceneType::TITLE);
	title_se.play();
	object_list.emplace("ClickToStart", std::make_shared<ClickToStart>(is_transition));
}

SceneType Title::Update(){
	for(auto& object : object_list){
		object.second->Update();
	}

	TransitionCondition();
	StartTrasition();

	return Type();
}

void Title::Draw(){
	//　背景
	drawTextureBox(-Window::WIDTH*0.5f, -Window::HEIGHT *0.5f, Window::WIDTH, Window::HEIGHT,
		0, 0, bg.width(), bg.height(),
		bg, Color(1, 1, 1));


	for (auto& object : object_list){
		object.second->Draw();
	}

	//　タイトルのロゴ
	drawTextureBox(-Window::WIDTH*0.5f, -Window::HEIGHT *0.5f, Window::WIDTH, Window::HEIGHT,
		0, 0, title_texture.width(), title_texture.height(),
		title_texture, Color(1, 1, 1));

}

//　遷移開始
void Title::StartTrasition(){
	if (is_transition)return;
	if (!app_env.isPushButton(Mouse::LEFT))return;
	title_se.stop();
	start_se.play();
	is_transition = !is_transition;		
}

//　遷移条件
void Title::TransitionCondition(){
	if (!is_transition)return;
	transiton_count++;

	if (transiton_count < TRANSITION_TIME)return;
	LoadScene(SceneType::GAME);
}