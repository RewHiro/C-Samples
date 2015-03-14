//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "EasingTest.hpp"

#include <iostream>

// アプリのウインドウサイズ
enum Window {
  WIDTH  = 1024,
  HEIGHT = 680
};



class Rect{
	Vec2f pos;
	Vec2f size;
	Color color;
	Easing<Vec2f> easing;
public:
	Rect(
		const Vec2f& pos,
		const Vec2f& size,
		const Color& color) :
		pos(pos),
		size(size),
		color(color),
		easing(Easing<Vec2f>(pos,EaseType::OUT_BACK))
	{
	}
	void Update(){
		pos = easing(Vec2f(0, 125), 1.0f);
	}

	void Draw(){
		drawFillBox(pos.x(), pos.y(), 
			size.x(), size.y(), 
			color,
			0.0f,Vec2f(1,1),Vec2f(size.x() *.5f,size.y() *.5f));
	}
};

// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
                 false, true);

  Rect rect = Rect(Vec2f(-460,180), Vec2f(200, 50), Color(1, 0, 0));

  while (app_env.isOpen()) {

	  rect.Update();

    // 描画準備
    app_env.setupDraw();

	rect.Draw();
    
    // 画面更新
    app_env.update();
  }
}
