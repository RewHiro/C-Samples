//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include <vector>

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
                 false, false);

  app_env.bgColor(Color(1, 1, 1));

  std::vector<Texture>miku_textures;

  miku_textures.emplace_back(Texture("res/miku1.png"));
  miku_textures.emplace_back(Texture("res/miku2.png"));
  miku_textures.emplace_back(Texture("res/miku3.png"));

  Texture miku_texture = miku_textures.at(0);

  while (app_env.isOpen()) {

	  if(app_env.isPushKey('1')){
		  miku_texture = miku_textures.at(0);
	  }
	  else if(app_env.isPushKey('2')){
		  miku_texture = miku_textures.at(1);
	  }
	  else if(app_env.isPushKey('3')){
		  miku_texture = miku_textures.at(2);
	  }

    // 描画準備
    app_env.setupDraw();

	drawTextureBox(0, 0, WIDTH, HEIGHT,
		0, 0, miku_texture.width(), miku_texture.height()*0.5f,
		miku_texture, Color(1, 1, 1),
		0.0f, Vec2f(0.5f, 0.5f), Vec2f(WIDTH*0.5f, HEIGHT*0.5f));
    
    // 画面更新
    app_env.update();
  }
}
