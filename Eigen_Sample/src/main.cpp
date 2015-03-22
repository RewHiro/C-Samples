//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"


enum Window {
  WIDTH  = 512,
  HEIGHT = 256
};


// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);

  Vec2f mouse_pos = env.mousePosition();
  
  while (env.isOpen()) {
    env.setupDraw();

    if (env.isPushKey('A')) {
      // マウス位置を記録
      mouse_pos = env.mousePosition();
    }
    if (env.isPushKey('S')) {
      // 記録したマウス位置へ変更
      env.mousePosition(mouse_pos);
    }

    Vec2f pos = env.mousePosition();
    drawFillCircle(pos.x(), pos.y(), 10, 10, 20, Color(1, 1, 1));
    
    
    env.update();
  }
}
