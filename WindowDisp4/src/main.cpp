//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib\font.hpp"
#include "lib\random.hpp"
#include <random>
#include <sstream>
#include <iomanip>
#include <array>

// MEMO
// Font→sizeを設定しないとデストラクタで消される

enum Window {
	WIDTH = 512,
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

	Vec2f hp_pos = Vec2f(10,140);
	Vec2f hp_size = Vec2f(150,25);

	Vec2f mp_pos = Vec2f(10,100);

	Vec2f score_pos = Vec2f(10,50);

	Vec2f life_pos = Vec2f(10,10);
	Vec2f life_size = Vec2f(32,32);

	Texture icon = Texture("res/icon.png");
	Font font = Font("res/VeraMono.ttf");

	Vec2f dis = Vec2f::Zero();

	PlayerData& player_data;

	bool is_drag = false;

	UI(
		Vec2f& pos,
		Vec2f& size,
		PlayerData& player_data,
		Font& font
		) :
		pos(pos),
		size(size),
		player_data(player_data)
	{
		this->font.size(20);
	}

	void Update(AppEnv& env){

		player_data.hp--;
		player_data.mp++;
		player_data.score++;

		if (player_data.hp < 0){
			player_data.hp = HP_MAX;
			player_data.life--;
			if (player_data.life < 0){
				player_data.life = LIFE_MAX;
			}
		}
		if (player_data.mp > MP_MAX)player_data.mp = 0;
		if (player_data.score > SCORE_LIMIT)player_data.score = 0;


		if (env.isPullButton(Mouse::LEFT)){
			is_drag = false;
		}
		if (is_drag){
			pos = env.mousePosition() - dis;
		}
	}

	bool Drag(AppEnv& env){
		if (PointToQuad(env.mousePosition(), pos, size)){
			is_drag = true;
			dis = env.mousePosition() - pos;
			return true;
		}
		return false;
	}

	void Draw(){
		DrawPanel();
		DrawHPUI();
		DrawMPUI();
		DrawScoreUI();
		DrawIconUI();
	}

private:
	void DrawPanel(){
		auto color = is_drag ? Color(1, 0, 0) : Color(1, 1, 1);
		drawFillBox(pos.x(), pos.y(), size.x(), size.y(),
			Color(0, 0, 0));
		drawBox(pos.x(), pos.y(), size.x(), size.y(),
			3, color);
	}

	void DrawHPUI(){
		auto ui_pos = pos + hp_pos;
		auto now_hp_size = hp_size.x() * player_data.hp / HP_MAX;
		drawFillBox(ui_pos.x(), ui_pos.y(), hp_size.x(), hp_size.y(),
			Color(1, 0, 0));
		drawFillBox(ui_pos.x(), ui_pos.y(), now_hp_size, hp_size.y(),
			Color(0, 1, 0));
		drawBox(ui_pos.x(), ui_pos.y(), hp_size.x(), hp_size.y(), 1,
			Color(1, 1, 1));
	}

	void DrawMPUI(){
		auto ui_pos = pos + mp_pos;
		std::ostringstream mp_text;
		mp_text << std::setw(3) << player_data.mp;
		font.draw("MP: " + mp_text.str() + "/100", ui_pos, Color(1, 1, 1));
	}

	void DrawScoreUI(){
		auto ui_pos = pos + score_pos;
		std::ostringstream score_text;
		score_text << std::setw(5) << player_data.score;
		font.draw("SCORE:" + score_text.str(), ui_pos, Color(1, 1, 1));
	}

	void DrawIconUI(){
		auto ui_pos = pos + life_pos;
		for (int i = 0; i < player_data.life; i++){
			drawTextureBox(ui_pos.x() + i * icon.width(), ui_pos.y(), icon.width(), icon.height(),
				0, 0, icon.width(), icon.height(),
				icon, Color(1, 1, 1));
		}
	}
};


// 
// メインプログラム
// 
int main() {
	AppEnv env(Window::WIDTH, Window::HEIGHT, false, true);

	Font font("res/VeraMono.ttf");
	font.size(20);

	Random random;
	random.setSeed(static_cast<u_int>(std::random_device()()));


	std::array<PlayerData, 3> players_data = {
		random.fromZeroToLast(100), random.fromZeroToLast(100), random.fromZeroToLast(99999), random.fromZeroToLast(3),
		random.fromZeroToLast(100), random.fromZeroToLast(100), random.fromZeroToLast(99999), random.fromZeroToLast(3),
		random.fromZeroToLast(100), random.fromZeroToLast(100), random.fromZeroToLast(99999), random.fromZeroToLast(3)
	};

	std::array<UI, 3> uies = {
		UI(Vec2f(0,0), Vec2f(180, 180), players_data.at(0),font),
		UI(Vec2f(-100,0), Vec2f(180, 180), players_data.at(1),font),
		UI(Vec2f(0,100), Vec2f(180, 180), players_data.at(2),font)
	};

	Vec2f dis = Vec2f::Zero();

	while (env.isOpen()) {

		for(auto& ui : uies){
			ui.Update(env);
		}

		for (auto it = uies.rbegin(); it != uies.rend(); it++){
			if (env.isPushButton(Mouse::LEFT)){
				if (it->Drag(env))break;
			}
		}

		env.setupDraw();
		for (auto& ui : uies){
			ui.Draw();
		}
		env.update();
	}
}
