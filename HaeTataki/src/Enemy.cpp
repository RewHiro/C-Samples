#include "Enemy.h"
#include <random>
#include "Scene.h"
#include "Collision.h"

Enemy::Enemy(AppEnv& app_env,ObjectInfo& object_info,int& point) :
Object(Vec2f(0,0),Vec2f(256,256),Color(1,1,1),object_info),
app_env(app_env),
point(point)
{
	random.setSeed(std::random_device()());
	pos = Vec2f(random.fromFirstToLast(-Window::WIDTH*.5f, Window::WIDTH*.5f),
		random.fromFirstToLast(-Window::HEIGHT*.5f, Window::HEIGHT*.5f));
	textures.emplace_back(Texture("res/miku.png"));
	textures.emplace_back(Texture("res/miku_hit.png"));
	texture = textures.at(0);
	std::array<Vec2f, 9>offset = {
		Vec2f(0, 0),
		Vec2f(2, 2),
		Vec2f(2, 0),
		Vec2f(2, -2),
		Vec2f(0, -2),
		Vec2f(-2, -2),
		Vec2f(-2, 0),
		Vec2f(-2, 2),
		Vec2f(0, 2)
	};
	effect_offset = offset;
	hit_pos = Vec2f(pos.x() - 60,pos.y()-size.y()*.5f);
	hit_size = Vec2f(160,240);
}

void Enemy::Update(){
	auto player_pos = object_info.Find("Player")->second->Positon();
	auto is_hit = Collision::PointRect(player_pos, hit_pos, hit_size);

	if(state == State::NORMAL){
		if(is_hit){
			if(app_env.isPushButton(Mouse::LEFT)){
			state = State::HIT;
			texture = textures.at(1);
			hit_se.play();
			point++;
			}
		}
	}
	if(state == State::HIT){
		effect_count++;
		if(effect_count == 20){
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

	//drawBox(hit_pos.x(), hit_pos.y(), hit_size.x(), hit_size.y(), 5.0f, color);
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
	effect_count = 0;
	texture = textures.at(0);
	hit_pos = Vec2f(pos.x() - 60, pos.y() - size.y()*.5f);
}