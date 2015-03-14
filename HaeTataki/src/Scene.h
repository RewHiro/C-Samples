#pragma once
#include "lib\appEnv.hpp"

enum class SceneType{
	TITLE,
	GAME,
	RESULT,
};

namespace Window {
	const int WIDTH = 512;
	const int HEIGHT = 512;
};

class Scene
{
	SceneType type;
protected:
	SceneType Type()const{ return type; }
	void LoadScene(const SceneType type){ this->type = type; }
	AppEnv& app_env;
public:
	Scene(AppEnv&);
	virtual ~Scene() = default;

	virtual SceneType Update() = 0;
	virtual void Draw() = 0;
};

