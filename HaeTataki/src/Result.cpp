#include "Result.h"


Result::Result(AppEnv& app_env):
Scene(app_env)
{
	LoadScene(SceneType::RESULT);
}


Result::~Result()
{
}
