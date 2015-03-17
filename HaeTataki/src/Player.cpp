#include "Player.h"


Player::Player(AppEnv& app_env, ObjectInfo& object_info) :
Object(Vec2f(0,0),Vec2f(256,256),Color(1,1,1),object_info),
app_env(app_env)
{
	textures.emplace_back(Texture("res/haetataki_1.png"));
	textures.emplace_back(Texture("res/haetataki_2.png"));
	texture = textures.at(0);
}

void Player::Update(){
	pos = app_env.mousePosition();
	if(app_env.isPushButton(Mouse::LEFT)){
		texture = textures.at(1);
	}
	else{
		texture = textures.at(0);
	}
}

void Player::Draw(){
	drawTextureBox(pos.x(), pos.y(), size.x(), size.y(),
		0, 0, texture.width(), texture.height(),
		texture, color,
		.0f,Vec2f(1,1),Vec2f(size.x()*.7f,size.y()*.85f));
}