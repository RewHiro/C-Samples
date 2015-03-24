//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib\font.hpp"
#include <sstream>
#include <iomanip>

enum Window {
  WIDTH  = 512,
  HEIGHT = 512
};

const int HP_MAX = 100;
const int MP_MAX = 100;
const int SCORE_LIMIT = 99999;
const int LIFE_MAX = 3;

bool PointToQuad(const Vec2f& point, const Vec2f& quad_pos, const Vec2f& quad_size){
	if (!(point.x() > quad_pos.x() && point.x() < quad_pos.x() + quad_size.x()))return false;
	if (!(point.y() > quad_pos.y() && point.y() < quad_pos.y() + quad_size.y()))return false;
	return true;
}

struct PlayerData{
	int hp;
	int mp;
	int score;
	int life;
};

struct UI{
	Vec2f pos;
	Vec2f size;

	Vec2f hp_pos;
	Vec2f hp_size;

	Vec2f mp_pos;

	Vec2f score_pos;

	Vec2f life_pos;
	Vec2f life_size;

	Texture icon;
	Font font;

	bool is_drag;
};

void DrawPanel(const UI& ui){
	auto color = ui.is_drag ? Color(1, 0, 0) : Color(1, 1, 1);
	drawFillBox(ui.pos.x(), ui.pos.y(), ui.size.x(), ui.size.y(),
		Color(0, 0, 0));
	drawBox(ui.pos.x(), ui.pos.y(), ui.size.x(), ui.size.y(),
		3, color);
}

void DrawHPUI(const UI& ui,const PlayerData& player_data){
	auto pos = ui.pos + ui.hp_pos;
	auto now_hp_size = ui.hp_size.x() * player_data.hp / HP_MAX;
	drawFillBox(pos.x(), pos.y(), ui.hp_size.x(), ui.hp_size.y(),
		Color(1, 0, 0));
	drawFillBox(pos.x(), pos.y(), now_hp_size, ui.hp_size.y(),
		Color(0, 1, 0));
	drawBox(pos.x(), pos.y(), ui.hp_size.x(), ui.hp_size.y(), 1,
		Color(1, 1, 1));
}

void DrawMPUI(UI& ui, const PlayerData& player_data){
	auto pos = ui.pos + ui.mp_pos;
	std::ostringstream mp_text;
	mp_text << std::setw(3) << player_data.mp;
	ui.font.draw("MP: " + mp_text.str() + "/100", pos, Color(1, 1, 1));
}

void DrawScoreUI(UI& ui, const PlayerData& player_data){
	auto pos = ui.pos + ui.score_pos;
	std::ostringstream score_text;
	score_text << std::setw(5) << player_data.score;
	ui.font.draw("SCORE:" + score_text.str(), pos, Color(1, 1, 1));
}

void DrawIconUI(const UI& ui, const PlayerData& player_data){
	auto pos = ui.pos + ui.life_pos;
	for (int i = 0; i < player_data.life; i++){
		drawTextureBox(pos.x() + i * ui.icon.width(), pos.y(), ui.icon.width(), ui.icon.height(),
			0, 0, ui.icon.width(), ui.icon.height(),
			ui.icon, Color(1, 1, 1));
	}
}

void StatusUI(UI& ui, const PlayerData& player_data){
	DrawPanel(ui);
	DrawHPUI(ui, player_data);
	DrawMPUI(ui, player_data);
	DrawScoreUI(ui, player_data);
	DrawIconUI(ui, player_data);
}


void Update(AppEnv& env,UI& ui,PlayerData& player_data,Vec2f& dis){

	player_data.hp--;
	player_data.mp++;
	player_data.score++;

	if (player_data.hp < 0){
		player_data.hp = HP_MAX;
		player_data.life--;
		if(player_data.life < 0){
			player_data.life = LIFE_MAX;
		}
	}
	if (player_data.mp > MP_MAX)player_data.mp = 0;
	if (player_data.score > SCORE_LIMIT)player_data.score = 0;
	
	if(env.isPushButton(Mouse::LEFT)){
		if(PointToQuad(env.mousePosition(),ui.pos,ui.size)){
			ui.is_drag = true;
			dis = env.mousePosition() - ui.pos;
		}
	}
	else if(env.isPullButton(Mouse::LEFT)){
		ui.is_drag = false;
	}
	if(ui.is_drag){
		ui.pos = env.mousePosition() - dis;
	}
}

// 
// メインプログラム
// 
int main() {
  AppEnv env(Window::WIDTH, Window::HEIGHT, false, true);
  
  const Texture icon("res/icon.png");
  Font font("res/VeraMono.ttf");
  font.size(20);

  PlayerData player_data = {
	  100,
	  0,
	  0,
	  3
  };

  UI ui = {
	  Vec2f::Zero(),Vec2f(180,180),
	  Vec2f(10,140),Vec2f(150,25),
	  Vec2f(10,100),
	  Vec2f(10,50),
	  Vec2f(10,10),Vec2f(icon.width(),icon.height()),
	  icon,font,false
  };

  Vec2f dis = Vec2f::Zero();

  while (env.isOpen()) {

	Update(env,ui,player_data,dis);

    env.setupDraw();
    
	StatusUI(ui, player_data);
    
    env.update();
  }
}
