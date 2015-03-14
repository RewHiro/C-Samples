#pragma once
#include "lib\vector.hpp"
#include "lib\graph.hpp"
class Object
{
protected:
	Vec2f pos;
	Vec2f size;
	Color color;
public:
	Object()= default;
	Object(const Vec2f& pos, const Vec2f& size,const Color& color):
		pos(pos),
		size(size),
		color(color){}

	virtual ~Object() = default;

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

