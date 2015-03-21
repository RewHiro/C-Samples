//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "Scene.h"
#include <array>


enum class SceneType{
	TITLE,
	STAGE,
	RESULT,
};

// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, true);

  std::array<Scene,3>scenes ={
	  Scene("res/bg1.png","res/chara1.png","res/text1.png"),
	  Scene("res/bg2.png", "res/chara2.png", "res/text2.png"),
	  Scene("res/bg3.png", "res/chara3.png", "res/text3.png")
  };


  int scene_count = 0;
  while (env.isOpen()) {

	  Scene& scene = scenes.at(scene_count % 3);
	  if(env.isPushButton(Mouse::LEFT)){
		  scene_count++;
	  }
    env.setupDraw();
    
	scene.Draw();

    
    env.update();
  }
}
