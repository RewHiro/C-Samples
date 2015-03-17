#include "UITime.h"
#include "Game.h"
#include <iostream>
UITime::UITime(int& count_time, ObjectInfo& object_info) :
Object(Vec2f(0,224),Vec2f(256,48),Color(0,1,1),object_info),
count_time(count_time)
{
}

void UITime::Update(){
	if(count_time == 60 * 3){
		color = Color(1, 0, 0);
	}
}

void UITime::Draw(){
	drawFillBox(pos.x(), pos.y(), size.x(), size.y(),
		Color(.5f, .5f, .5f),
		.0f, Vec2f(1, 1), Vec2f(size.x()*.5f, size.y()*.5f));


	float width = (static_cast<float>(count_time) / Game::MaxTime())*size.x();
	drawFillBox(pos.x(), pos.y(), width, size.y(),
		color,
		.0f, Vec2f(1, 1), Vec2f(size.x()*.5f, size.y()*.5f));

	drawBox(pos.x(), pos.y(), size.x(), size.y(), 3,
		Color(1, 1, 1)
		, .0f, Vec2f(1, 1), Vec2f(size.x()*.5f, size.y()*.5f));
}
