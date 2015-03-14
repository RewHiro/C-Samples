#pragma once
#include "Object.h"
class ClickToStart :
	public Object
{
	const Texture texture = Texture("res/click_to_start.png");
	float pitching_radian = .0f;
	float alpha_radian = .0f;
	const float START_POS = -96.0f;
	const float AMPLITUDE = 8.0f;
	const bool& is_transition;
public:
	ClickToStart(const bool& is_transiton);

	void Update();
	void Draw();

private:
	void DuringTransition();
	void Normal();
};

