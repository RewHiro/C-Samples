#pragma once
#include "Scene.h"
class Result :
	public Scene
{
public:
	Result(AppEnv&);
	~Result();

	SceneType Update(){
		if(app_env.isPushButton(Mouse::LEFT)){
			LoadScene(SceneType::TITLE);
		}
		return Type();
	}
	void Draw(){
	}
};

