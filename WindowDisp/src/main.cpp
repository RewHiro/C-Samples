//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib\font.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>

enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};

const float HP_SIZE = 150;

bool PointToQuad(const Vec2f& point, const Vec2f& quad_pos, const Vec2f& quad_size){
	if (!(point.x() > quad_pos.x() && point.x() < quad_pos.x() + quad_size.x()))return false;
	if (!(point.y() > quad_pos.y() && point.y() < quad_pos.y() + quad_size.y()))return false;
	return true;
}


void DrawPanel(const Vec2f& pos, const Vec2f& size, const Color& color){
	drawFillBox(pos.x(), pos.y(), size.x(), size.y(),
		Color(0, 0, 0));
	drawBox(pos.x(), pos.y(), size.x(), size.y(),
		3, color);

	
}

void DrawHPUI(const Vec2f& parent_pos, const Vec2f& parent_size, int hp){
	//　HP
	auto hp_pos = parent_pos + Vec2f(10, parent_size.y() - 40);
	{
		auto size = HP_SIZE * hp / 100;
		drawFillBox(hp_pos.x(), hp_pos.y(), HP_SIZE, 25,
			Color(1, 0, 0));
		drawFillBox(hp_pos.x(), hp_pos.y(), size, 25,
			Color(0, 1, 0));
		drawBox(hp_pos.x(), hp_pos.y(), HP_SIZE, 25, 1,
			Color(1, 1, 1));
	}
}

void DrawMPUI(const Vec2f& parent_pos, const Vec2f& parent_size, int mp, Font& font){
	//　MP
	auto mp_pos = parent_pos + Vec2f(10, parent_size.y() - 80);
	std::ostringstream mp_text;
	mp_text << std::setw(3) << mp;
	font.draw("MP: " + mp_text.str() + "/100", mp_pos, Color(1, 1, 1));
}

void DrawScoreUI(const Vec2f& parent_pos, const Vec2f& parent_size, int score, Font& font){
	//　SCORE
	auto score_pos = parent_pos + Vec2f(10, 50);
	std::ostringstream score_text;
	score_text << std::setw(5) << score;
	font.draw("SCORE:" + score_text.str(), score_pos, Color(1, 1, 1));
}

void DrawIconUI(const Vec2f& pos, const Vec2f& size, int life, const Texture& texture){
	auto icon_pos = pos + Vec2f(10, 10);
	for (int i = 0; i < life; i++){
		drawTextureBox(icon_pos.x() + i * texture.width(), icon_pos.y(), texture.width(), texture.height(),
			0, 0, texture.width(), texture.height(),
			texture, Color(1, 1, 1));
	}
}

// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);
  env.bgColor(Color(.2f, .2f, .2f));

  Vec2f pos = Vec2f::Zero();
  Vec2f size(180, 180);
  
  Font font("res/VeraMono.ttf");
  font.size(20);

  int hp = 100;

  int mp = 0;
  int score = 0;

  bool is_hit = false;
  Vec2f dis = Vec2f::Zero();
  const Texture texture("res/icon.png");
  int life = 3;

  Color color(1, 1, 1);

  while (env.isOpen()) {
	
	if(env.isPushButton(Mouse::LEFT)){
		if(PointToQuad(env.mousePosition(),pos,size)){
			is_hit = true;
			dis = env.mousePosition() - pos;
		}
	}
	else if(env.isPullButton(Mouse::LEFT)){
		is_hit = false;
	}

	if (is_hit){
		color = Color(1, 0, 0);
		pos = env.mousePosition() - dis;
		std::cout << dis << std::endl;
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
	if (mp > 100)mp = 0;

	score++;
	if (score > 99999)score = 0;

    env.setupDraw();
    
	DrawPanel(pos,size,color);
	DrawHPUI(pos, size, hp);
	DrawMPUI(pos, size, mp, font);
	DrawScoreUI(pos, size, score, font);
	DrawIconUI(pos, size, life, texture);
    
    env.update();
  }
}
