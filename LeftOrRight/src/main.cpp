//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "SceneManager.h"



// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, true);
  SceneManager scene_manager(env,SceneType::TITLE);
  while (env.isOpen()) {
	scene_manager.Update();
  }
}
