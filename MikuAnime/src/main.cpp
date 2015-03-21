//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"

#include <array>
#include <iostream>

enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};


// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, true);

  env.bgColor(Color(.5f, .5f, .5f));

  std::array<Texture, 6>textures={
	  Texture("res/miku_1.png"),
	  Texture("res/miku_2.png"),
	  Texture("res/miku_3.png"),
	  Texture("res/miku_4.png"),
	  Texture("res/miku_5.png"),
	  Texture("res/miku_6.png"),
  };
  Color color(1, 1, 1);

  int effect_count = 0;

  while (env.isOpen()) {
    env.setupDraw();
	effect_count++;
	if(env.isPressKey('A')){
		effect_count += 3;
	}

	drawTextureBox(0, 0, 310, 270,
		0, 0, 310, 270,
		textures.at(effect_count / 30 % textures.size()), color,
		.0f, Vec2f(1, 1), Vec2f(310 * .5f, 270 * .5f));
    
    env.update();
  }
}
