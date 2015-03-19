#pragma once
#include "Object.h"
class ClickToTitle :
	public Object
{
	const Texture texture = Texture("res/click_to_title.png");
	float pitching_radian = .0f;
public:
	ClickToTitle(ObjectInfo& object_info);

	void Update();
	void Draw();
};

