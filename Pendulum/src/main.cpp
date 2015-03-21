//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"


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
  const Texture texture("res/miku.png");
  Color color(1, 1, 1);
  float radian = .0f;

  while (env.isOpen()) {
    env.setupDraw();
	radian += static_cast<float>(M_1_PI * .1f);
	drawTextureBox(0, 100, 256, 256,
		0, 0, texture.width(), 256,
		texture, color,
		M_PI / 6 * std::sinf(radian),Vec2f(1,1),Vec2f(texture.width()*.5f,256+50));
    
    env.update();
  }
}
