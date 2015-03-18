//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"


enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};


const float JUMP_POWER = 20.0f;
const float GRAVITY_POWER = 1.0f;

// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, true);
  
  Vec2f pos(0,0);
  Color color(1, 1, 1);
  float velocity_y = 0;
  bool is_jump = false;

  while (env.isOpen()) {

	  if(!is_jump){
		if(env.isPushButton(Mouse::LEFT)){
			is_jump = !is_jump;
			velocity_y = JUMP_POWER;
		}
	  }
	  else {
		  pos.y() += velocity_y + 0.5f * -GRAVITY_POWER;
		  velocity_y += -GRAVITY_POWER;
		  if(pos.y() < 0){
			  is_jump = !is_jump;
			  pos.y() = 0;
		  }
	  }

    env.setupDraw();
    
	drawFillCircle(pos.x(), pos.y(), 32, 32, 20, color);
    
    env.update();
  }
}
