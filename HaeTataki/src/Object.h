#pragma once
#include "lib\vector.hpp"
#include "lib\graph.hpp"
#include "ObjectInfo.h"


class Object
{
protected:
	ObjectInfo& object_info;
	Vec2f pos;
	Vec2f size;
	Color color;
public:
	Object()= default;
	Object(const Vec2f& pos, const Vec2f& size,const Color& color,ObjectInfo& object_info):
		pos(pos),
		size(size),
		color(color),
		object_info(object_info){}

	virtual ~Object() = default;

	virtual void Update() = 0;
	virtual void Draw() = 0;

	Vec2f Positon()const{
		return pos;
	}
};

