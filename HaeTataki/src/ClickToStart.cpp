#include "ClickToStart.h"
#include "lib\graph.hpp"



ClickToStart::ClickToStart(const bool& is_transiton, ObjectInfo& object_info) :
Object(Vec2f(0, START_POS), Vec2f(512, 128), Color(1, 1, 1),object_info),
is_transition(is_transiton)
{
}

void ClickToStart::Update(){
	Normal();
	DuringTransition();
	pos.y() = START_POS + AMPLITUDE * std::sinf(pitching_radian);
}

void ClickToStart::Draw(){
	drawTextureBox(pos.x(), pos.y(), size.x(), size.y(),
		0, 0, texture.width(), texture.height(),
		texture, color,
		.0f, Vec2f(1, 1), Vec2f(size.x() * 0.5f, size.y() * 0.5f));
}

//Å@ëJà⁄íÜ
void ClickToStart::DuringTransition(){
	if (!is_transition)return;
	pitching_radian = 0.f;
	alpha_radian += static_cast<float>(M_2_SQRTPI);
	color.alpha() = std::sinf(alpha_radian);
}

//Å@í èÌ
void ClickToStart::Normal(){
	if (is_transition)return;
	pitching_radian += static_cast<float>(M_1_PI * 0.5f);
}