#pragma once
#include "Object.h"
class UITime :
	public Object
{
	const int& count_time;

public:
	UITime(int& count_time);

	void Update();
	void Draw();
};

