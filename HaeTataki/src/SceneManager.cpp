#include "SceneManager.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include <unordered_map>
#include <functional>

SceneManager::SceneManager(AppEnv& app_env, const SceneType type) :
app_env(app_env),
scene(std::make_shared<Title>(app_env)),
scene_type(type)
{

}

void SceneManager::Update(){
	auto now_scene_type = scene->Update();
	
	app_env.setupDraw();
	scene->Draw();
	app_env.update();

	if(scene_type != now_scene_type){
		scene = Create(now_scene_type);
		scene_type = now_scene_type;
	}
}

std::shared_ptr<Scene> SceneManager::Create(const SceneType type){
	static const std::unordered_map<SceneType,std::function<std::shared_ptr<Scene>()>> scene_list = {
		{
			SceneType::TITLE,
			[&]{return std::make_shared<Title>(app_env); }
		},
		{
			SceneType::GAME,
			[&]{return std::make_shared<Game>(app_env); }
		},
		{
			SceneType::RESULT,
			[&]{return std::make_shared<Result>(app_env); }
		}
	};
	return (scene_list.find(type))->second();
}