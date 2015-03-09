#pragma once
#include "lib\appEnv.hpp"
#include "Camera.h"
#include <algorithm>
#include <memory>

class Object{
protected:
	Vec2f pos;
	Vec2f size;
	std::string name = "GameObject";

public:
	Object() = default;
	Object(const Vec2f& pos, const Vec2f& size):
	pos(pos),
	size(size)
	{}

	Vec2f Position()const{return pos;}
	Vec2f Size()const{ return size; }

	std::string& Name(){ return name; }

	virtual void Update(){
	};
	virtual void Draw() = 0;
};