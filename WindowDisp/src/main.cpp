//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib\font.hpp"

enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};


bool PointToQuad(const Vec2f& point, const Vec2f& quad_pos, const Vec2f& quad_size){
	if (!(point.x() > quad_pos.x() && point.x() < quad_pos.x() + quad_size.x()))return false;
	if (!(point.y() > quad_pos.y() && point.y() < quad_pos.y() + quad_size.y()))return false;
	return true;
}

// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);
  env.bgColor(Color(.2f, .2f, .2f));

  Vec2f pos = Vec2f::Zero();
  float size = 180;
  
  Font font("res/VeraMono.ttf");
  font.size(20);

  int hp = 100;
  float hp_size = 150;
  int mp = 0;
  int score = 0;

  const Texture texture("res/icon.png");
  int life = 3;

  Color color(1, 1, 1);

  while (env.isOpen()) {
	
	if(env.isPressButton(Mouse::LEFT)){
		if(PointToQuad(env.mousePosition(),pos,Vec2f(size,size))){
			color = Color(1, 0, 0);
		}
	}
	else{
		color = Color(1, 1, 1);
	}

	hp--;
	if (hp < 0){
		hp = 100;
		life--;
		if(life < 0){
			life = 3;
		}
	}
	mp++;
	mp = mp % 100;

	score++;
	if (score > 99999)score = 0;

    env.setupDraw();
    
	drawFillBox(pos.x(), pos.y(), size, size,
		Color(0, 0, 0));
	drawBox(pos.x(), pos.y(), size, size,
		3, color);

	//　HP
	auto hp_pos = pos + Vec2f(10, size - 40);
	{
		auto size = hp_size * hp / 100;
		drawFillBox(hp_pos.x(), hp_pos.y(), hp_size, 25,
			Color(1, 0, 0));
		drawFillBox(hp_pos.x(), hp_pos.y(), size, 25,
			Color(0, 1, 0));
		drawBox(hp_pos.x(), hp_pos.y(), hp_size, 25, 1,
			Color(1, 1, 1));
	}

	//　MP
	auto mp_pos = pos + Vec2f(10, size - 80);
	font.draw("MP: " + std::to_string(mp) + "/100", mp_pos, Color(1, 1, 1));
    
	//　SCORE
	auto score_pos = pos + Vec2f(10, 50);
	font.draw("SCORE:" + std::to_string(score),score_pos,Color(1,1,1));

	auto icon_pos = pos + Vec2f(10, 10);
	for (int i = 0; i < life; i++){
		drawTextureBox(icon_pos.x() + i * texture.width(), icon_pos.y(), texture.width(), texture.height(),
			0, 0, texture.width(), texture.height(),
			texture, Color(1, 1, 1));
	}

    env.update();
  }
}
