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
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);
  env.bgColor(Color(.5f, .5f, .5f));

  const Texture texture("res/miku.png");
  Color color(1, 1, 1);

  auto angle = .0f;

  while (env.isOpen()) {

	  angle = std::fmodf(angle + M_1_PI*.1f, M_PI * 2);

	  auto scalling = std::fabsf(std::sinf(angle));
	  auto colorling = std::fabsf(std::sinf(angle));

	  color.blue() = colorling*.6f +.4f;
	  color.red() = colorling*.6f + .4f;
	  color.green() = colorling*.6f + .4f;

	  auto cutting_y = angle < M_PI ? .0f : 270.0f;

	  env.setupDraw();
		  drawTextureBox(0, 0, 256, 256,
			  0, cutting_y, 256, 256,
			  texture, color,
			  .0f, Vec2f(scalling, 1), Vec2f(256 * .5f, 256 * .5f));

	  env.update();
  }
}
