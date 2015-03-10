//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "EasingTest.hpp"

#include <iostream>

// アプリのウインドウサイズ
enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};


// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
                 false, true);

  Easing<float>test(EaseType::INOUT_BOUNCE);
  auto a = .5f;

  auto time = 0;
  auto x = 0.0f;
  while (app_env.isOpen()) {

	x = test(100,-200,3.0f,1.0f);
	  //x = test.MoveTo(100, 100, 4.0f);


	  DOUT << x << std::endl;
    // 描画準備
    app_env.setupDraw();

    
    // 画面更新
    app_env.update();
  }
}
