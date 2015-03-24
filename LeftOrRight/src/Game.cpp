#include "Game.h"

bool PointToQuad(const Vec2f& point, const Vec2f& quad_pos, const Vec2f& quad_size){
	if (!(point.x() > quad_pos.x() && point.x() < quad_pos.x() + quad_size.x()))return false;
	if (!(point.y() > quad_pos.y() && point.y() < quad_pos.y() + quad_size.y()))return false;
	return true;
}

Game::Game(AppEnv& app_env):
Scene(app_env)
{
	for (int i = 0; i < card_info.size(); i++){
		float offset_x = CUTTING_SIZE.x() * (i % CUTTING_NUM);
		float offset_y = CUTTING_SIZE.y() * (i / CUTTING_NUM);
		card_info.at(i) = { Vec2f(offset_x, offset_y), Vec2f(72, 96), offset_x + 1};
	}
	random.seed(std::random_device()());
	std::shuffle(card_info.begin(), card_info.end(),random);
	LoadScene(SceneType::GAME);
}

SceneType Game::Update(){
	time--;
	if(time < 0){
		LoadScene(SceneType::RESULT);
	}
	if(PointToQuad(app_env.mousePosition(),left_pos - card_size * .5f,card_size)){
		left_color = Color(1, 0.5f, 0.5f);
		if(app_env.isPushButton(Mouse::LEFT)){
			if (card_info.at(card_index).num >= card_info.at(card_index + 1).num){
				Point() += 1;
				card_index += 2;
				if(card_index > 51){
					card_index = 0;
					LoadScene(SceneType::RESULT);
				}
			}
			else {
				card_index += 2;
				if (card_index > 51){
					card_index = 0;
					LoadScene(SceneType::RESULT);
				}
			}
		}
	}
	else{
		left_color = Color(1, 1, 1);
	}

	if (PointToQuad(app_env.mousePosition(), right_pos - card_size * .5f, card_size)){
		right_color = Color(1, 0.5f, 0.5f);
		if (app_env.isPushButton(Mouse::LEFT)){
			if (card_info.at(card_index + 1).num >= card_info.at(card_index).num){
				Point() += 1;
				card_index += 2;
				if (card_index > 51){
					card_index = 0;
					LoadScene(SceneType::RESULT);
				}
			}
			else {
				card_index += 2;
				if (card_index > 51){
					card_index = 0;
					LoadScene(SceneType::RESULT);
				}
			}
		}
	}
	else{
		right_color = Color(1, 1, 1);
	}

	return Type();
}

void Game::Draw(){

	drawTextureBox(left_pos.x(), left_pos.y(), card_size.x(), card_size.y(),
		card_info.at(card_index).texture_pos.x(), card_info.at(card_index).texture_pos.y(), card_info.at(card_index).texture_size.x(), card_info.at(card_index).texture_size.y(),
		card_texture, left_color,
		.0f, Vec2f::Ones(), Vec2f(card_info.at(card_index).texture_size.x()*.5f, card_info.at(card_index).texture_size.y()*.5f));

	drawTextureBox(right_pos.x(), right_pos.y(), card_size.x(), card_size.y(),
		card_info.at(card_index + 1).texture_pos.x(), card_info.at(card_index + 1).texture_pos.y(), card_info.at(card_index + 1).texture_size.x(), card_info.at(card_index + 1).texture_size.y(),
		card_texture, right_color,
		.0f, Vec2f::Ones(), Vec2f(card_info.at(card_index + 1).texture_size.x()*.5f, card_info.at(card_index + 1).texture_size.y()*.5f));

	auto one_point = Point() % 10;
	auto ten_point = Point() / 10;
	auto x = -Window::WIDTH*.5f + 30;

	for (int i = 0; i < ten_point; i++){
		drawFillCircle(x, Window::HEIGHT * .5f - 30, 20, 20, 20, Color(1, 0, 0));
		x += 35;
	}
	for (int i = 0; i < one_point; i++){
		drawFillCircle(x, Window::HEIGHT * .5f - 30, 10, 10, 20, Color(1, 1, 0));
		x += 25;
	}

	auto size_x = static_cast<float>(time) / MAX_TIME * 300;
	drawFillBox(0, -150, size_x, 50,
		Color(0, 1, 1),
		.0f,Vec2f::Ones(),Vec2f(300*.5f,50*.5f));
	drawBox(0, -150, 300, 50, 3,
		Color(1, 1, 1),
		.0f, Vec2f::Ones(), Vec2f(300 * .5f, 50 * .5f));
}
