#pragma once
#include "lib\appEnv.hpp"
#include "Scene.h"
#include <memory>

class SceneManager
{
	AppEnv& app_env;
	std::shared_ptr<Scene> scene;
	SceneType scene_type;

	std::shared_ptr<Scene> Create(const SceneType type);

public:
	SceneManager(AppEnv&,const SceneType);

	SceneManager() = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	void Update();


};