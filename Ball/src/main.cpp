//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib\random.hpp"
#include <random>
#include <algorithm>

// アプリのウインドウサイズ
enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};


//　重力の大きさ
const float GRAVITY_POWER = 1.0f;


//　xが最小値より下だった場合、最小値を返し、
//　xが最大値より上だった場合、最大値を返し、
//　それ以外だったらxを返す。
//
//　x：クランプする値
//　min：最小値
//　max：最大値
template<typename T>
T Clamp(
	const T& x,
	const T& min,
	const T& max
	)
{
	return std::min(std::max(x, min), max);
}

// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
                 false, false);

  //　乱数生成
  Random random;
  random.setSeed(std::random_device()());

  //　ボールの定義
  struct Ball{
	  Vec2f pos;
	  Vec2f speed;
	  Vec2f radius = Vec2f(10.0f, 10.0f);
	  Color color;
	  AppEnv& app_env;

	  Ball(AppEnv& app_env):
		  app_env(app_env){}

	  //　更新
	  void Update(){
		  pos += speed;
		  Gravity();
		  Bounce();
	  }

	  //　描画
	  void Draw(){
		  drawFillCircle(pos.x(), pos.y(),
			  radius.x(), radius.y(),
			  10,
			  color);
	  }

  private:

	  //　重力
	  void Gravity(){
		  if (!app_env.isPressKey('G'))return;
		  speed.y() += -GRAVITY_POWER;
	  }

	  //　壁に当たったら跳ね返す
	  void Bounce(){
		  if(pos.x() - radius.x() < -WIDTH*0.5f || 
			  pos.x() + radius.x() > WIDTH*0.5f){
			  pos.x() = Clamp(pos.x(), -WIDTH * 0.5f + radius.x(), WIDTH * 0.5f - radius.x());
			  speed.x() *= -1;
		  }
		  if (pos.y() - radius.y() < -HEIGHT*0.5f ||
			  pos.y() + radius.y() > HEIGHT*0.5f){
			  pos.y() = Clamp(pos.y(), -HEIGHT * 0.5f + radius.y(), HEIGHT * 0.5f - radius.y());
			  speed.y() *= -1;
		  }
	  }
  };

  Ball ball(app_env);

  const Vec2f INIT_POS = Vec2f(200.0f, 200.0f);
  const float SPPED_POWER = 5.0f;

  ball.pos = Vec2f(
	  random.fromFirstToLast(-INIT_POS.x(), INIT_POS.x()),
	  random.fromFirstToLast(-INIT_POS.y(), INIT_POS.y()));
  
  ball.speed = Vec2f(
	  random.fromFirstToLast(-SPPED_POWER, SPPED_POWER),
	  random.fromFirstToLast(-SPPED_POWER, SPPED_POWER));

  ball.color = Color(
	  random.fromFirstToLast(0.5f, 1.0f),
	  random.fromFirstToLast(0.5f, 1.0f),
	  random.fromFirstToLast(0.5f, 1.0f));

  while (app_env.isOpen()) {
    
	ball.Update();
    
    // 描画準備
    app_env.setupDraw();

	ball.Draw();
    
    // 画面更新
    app_env.update();
  }
}
