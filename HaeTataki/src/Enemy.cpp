#include "Enemy.h"
#include <random>
#include "Scene.h"
#include "Collision.h"

Enemy::Enemy(AppEnv& app_env,ObjectInfo& object_info) :
Object(Vec2f(0,0),Vec2f(256,256),Color(1,1,1),object_info),
app_env(app_env)
{
	random.setSeed(std::random_device()());
	pos = Vec2f(random.fromFirstToLast(-Window::WIDTH*.5f, Window::WIDTH*.5f),
		random.fromFirstToLast(-Window::HEIGHT*.5f, Window::HEIGHT*.5f));
	textures.emplace_back(Texture("res/miku.png"));
	textures.emplace_back(Texture("res/miku_hit.png"));
	texture = textures.at(0);
	std::array<Vec2f, 9>offset = {
		Vec2f(0, 0),
		Vec2f(1, 1),
		Vec2f(1, 0),
		Vec2f(1, -1),
		Vec2f(0, -1),
		Vec2f(-1, -1),
		Vec2f(-1, 0),
		Vec2f(-1, 1),
		Vec2f(0, 1)
	};
	effect_offset = offset;
}

void Enemy::Update(){
	auto player_pos = object_info.Find("Player")->second->Positon();
	auto is_hit = Collision::PointCenterRect(player_pos, pos, size);

	if(is_hit){
		if(app_env.isPushButton(Mouse::LEFT)){
		state = State::HIT;
		}
	}
	if(state == State::HIT){
		effect_count++;
		if(effect_count == 60 * 2){
			Reset();
		}
	}
}

void Enemy::Draw(){
	NormalDraw();
	EffectDraw();
}

void Enemy::NormalDraw(){
	if (state != State::NORMAL)return;
	drawTextureBox(pos.x(), pos.y(), size.x(), size.y(),
		0, 0, 256, 256,
		texture, color,
		.0f, Vec2f(1, 1), Vec2f(size.x()*.5f, size.y()*.5f));
}

void Enemy::EffectDraw(){
	if (state != State::HIT)return;
	int effect_array_num = effect_count / 2 % 9;

	drawTextureBox(pos.x() + effect_offset.at(effect_array_num).x(), pos.y() + effect_offset.at(effect_array_num).y(), size.x(), size.y(),
		0, 0, 256, 256,
		texture, color,
		.0f, Vec2f(1, 1), Vec2f(size.x()*.5f, size.y()*.5f));
}

void Enemy::Reset(){
	state = State::NORMAL;
	pos = Vec2f(random.fromFirstToLast(-Window::WIDTH*.5f, Window::WIDTH*.5f),
		random.fromFirstToLast(-Window::HEIGHT*.5f, Window::HEIGHT*.5f));
}