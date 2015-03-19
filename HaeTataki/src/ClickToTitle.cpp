#include "ClickToTitle.h"


ClickToTitle::ClickToTitle(ObjectInfo& object_info):
Object(Vec2f(0,-96),Vec2f(512,128),Color(1,1,1),object_info)
{
}


void ClickToTitle::Update(){
	pitching_radian += static_cast<float>(M_1_PI * 0.25f);
	pos.y() = -96 + 10.0f * std::sinf(pitching_radian);
}

void ClickToTitle::Draw(){
	drawTextureBox(pos.x(), pos.y(), texture.width(), texture.height(),
		0, 0, texture.width(), texture.height(),
		texture, Color(1, 1, 1),
		.0f, Vec2f(1, 1), Vec2f(texture.width()*.5f, texture.height()*.5f));
}