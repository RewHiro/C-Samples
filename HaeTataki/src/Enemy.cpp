#include "Enemy.h"
#include <random>
#include "Scene.h"
#include <iostream>

Enemy::Enemy(std::weak_ptr<Object>col_pos) :
Object(Vec2f(0,0),Vec2f(256,256),Color(1,1,1)),
col_pos(col_pos)
{
	random.setSeed(std::random_device()());
	pos = Vec2f(random.fromFirstToLast(-Window::WIDTH*.5f, Window::WIDTH*.5f),
		random.fromFirstToLast(-Window::HEIGHT*.5f, Window::HEIGHT*.5f));
	textures.emplace_back(Texture("res/miku.png"));
	textures.emplace_back(Texture("res/miku_hit.png"));
	texture = textures.at(0);
}

void Enemy::Update(){
	DOUT << col_pos.lock()->Positon() << std::endl;
}

void Enemy::Draw(){
	drawTextureBox(pos.x(), pos.y(), size.x(), size.y(),
		0, 0, 256, 256,
		texture, color,
		.0f, Vec2f(1, 1), Vec2f(size.x()*.5f, size.y()*.5f));
}