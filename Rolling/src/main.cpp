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
  bool is_switch = false;

  while (env.isOpen()) {

	  angle += M_1_PI*.1f;
	  
	  auto scalling = std::fabsf(std::sinf(angle));
	  auto colorling = std::fabsf(std::sinf(angle));

	  color.blue() = colorling*.5f +.5f;
	  color.red() = colorling*.5f + .5f;
	  color.green() = colorling*.5f + .5f;

	  if (angle > M_PI){
		  angle = .0f;
		  is_switch = !is_switch;
	  }

	  env.setupDraw();
	  if(!is_switch){
		  drawTextureBox(0, 0, 256, 256,
			  0, 0, 256, 256,
			  texture, color,
			  .0f, Vec2f(scalling, 1), Vec2f(256 * .5f, 256 * .5f));
	  }
	  else{
		drawTextureBox(0, 0, 256, 256,
			0, 266, 256, 256,
			texture, color,
			.0f, Vec2f(scalling, 1), Vec2f(256 * .5f, 256 * .5f));
	  }

	  env.update();
  }
}
