#pragma once
#include "Scene.h"
class Result :
	public Scene
{
public:
	Result(AppEnv&);
	~Result();

	SceneType Update(){
		return Type();
	}
	void Draw(){
	}
};

